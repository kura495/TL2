#include "TextureConverter.h"

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath, int numOptions, char* options[])
{
	LoadWICTextureFromFile(filePath);

	SaveDDSTextureToFile(numOptions, options);
}

void TextureConverter::OutputUsage()
{
	printf("画像ファイルをWIC形式からDDS形式に変換します。\n");
	printf("\n");
	printf("TextureConverter [ドライブ:][パス][ファイル名]\n");
	printf("\n");
	printf("[ドライブ:][パス][ファイル名]:変換したいWIC形式の画像ファイルを指定します。\n");
	printf("[-ml level]:ミップレベルを指定します。0を指定すると1x1までのフルミップマップチェーンを作成します。\n");
}

void TextureConverter::SaveDDSTextureToFile(int numOptions, char* options[])
{
	DirectX::ScratchImage mipChain;

	HRESULT result;

	size_t mipLevel = 0;

	//ミップマップレベル指定を検索
	for (int i = 0; i < numOptions;i++) {
		if (std::string(options[i]) == "-ml") {
			//ミップレベル指定
			mipLevel = std::stoi(options[i + 1]);
			break;
		}
	}

	//ミップマップ生成
	result = DirectX::GenerateMipMaps(scratchImage_.GetImages(),scratchImage_.GetImageCount(),scratchImage_.GetMetadata(),DirectX::TEX_FILTER_FLAGS::TEX_FILTER_DEFAULT, mipLevel,mipChain);

	if (SUCCEEDED(result)) {
		//イメージとメタデータを、ミップマップ版で置き換える
		scratchImage_ = std::move(mipChain);
		metadata_ = scratchImage_.GetMetadata();
	}

	//圧縮形式に変換
	DirectX::ScratchImage converted;
	result = DirectX::Compress(scratchImage_.GetImages(),scratchImage_.GetImageCount(),metadata_,DXGI_FORMAT_BC7_UNORM_SRGB, DirectX::TEX_COMPRESS_FLAGS::TEX_COMPRESS_BC7_QUICK | DirectX::TEX_COMPRESS_FLAGS::TEX_COMPRESS_SRGB_OUT | DirectX::TEX_COMPRESS_FLAGS::TEX_COMPRESS_PARALLEL,1.0f,converted);
	if (SUCCEEDED(result)) {
		scratchImage_ = std::move(converted);
		metadata_ = scratchImage_.GetMetadata();
	}

	//読み込んだテクスチャをSRGBとして扱う
	metadata_.format = DirectX::MakeSRGB(metadata_.format);

	//出力ファイル名を設定
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";
	//DDSファイル書き出し
	result = DirectX::SaveToDDSFile(scratchImage_.GetImages(),scratchImage_.GetImageCount(),metadata_,DirectX::DDS_FLAGS::DDS_FLAGS_NONE,filePath.c_str());
	assert(SUCCEEDED(result));
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
	size_t pos1;
	std::wstring exceptExt;

	//区切り文字'.'が出てくる一番最後の部分を検索
	pos1 = filePath.find('.');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos) {
		//区切り文字の後ろをファイル拡張子として保存
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		//区切り文字の前までを抜き出す
		exceptExt = filePath.substr(0,pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}

	//区切り文字'\\'が出てくる一番最後の部分を検索
	pos1 = exceptExt.find('\\');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos) {
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0,pos1 + 1);
		//区切り文字の後ろをファイル名として保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}
	
	//区切り文字'/'が出てくる一番最後の部分を検索
	pos1 = exceptExt.find('/');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos) {
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイル名として保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}
	//区切り文字がないとき
	directoryPath_ = L"";
	fileName_ = exceptExt;

	return;
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	// ファイルパスをワイド文字列に変換する
	std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);

	// WICテクスチャのロード
	HRESULT hr = LoadFromWICFile(wFilePath.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(hr));

	// 読み込んだテクスチャのファイルパスを分解する
	SeparateFilePath(wFilePath);
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
	// ワイド文字列に変換した際の文字数を計算
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	// ワイド文字列を生成
	std::wstring wString;
	wString.resize(filePathBufferSize);

	// 変換
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);

	// 返還する
	return wString;
}
