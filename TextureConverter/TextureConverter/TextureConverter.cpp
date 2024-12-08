#include "TextureConverter.h"

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{
	LoadWICTextureFromFile(filePath);
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
	size_t pos1;
	std::wstring exceptExt;

	//区切り文字'.'が出てくる一番最後の部分を検索
	pos1 = filePath.find('.');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos) {
		//区切り文字の後ろをファイル拡張子としてオゾン
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		//区切り文字の前までを抜き出す
		exceptExt = filePath.substr(0,pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	// ファイルパスをワイド文字列に変換する
	std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);

	// WICテクスチャのロード
	HRESULT hr = LoadFromWICFile(wFilePath.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(hr));

	//// 読み込んだテクスチャのファイルパスを分解する
	//SeparateFilePath(wFilePath);
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
