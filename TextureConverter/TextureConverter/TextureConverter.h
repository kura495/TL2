#pragma once
#include <string>
#include <Windows.h>
#include "../externals/DirectXTex/DirectXTex.h"

//テクスチャコンバーター
class TextureConverter
{
public:
	/// <summary>
	/// テクスチャをWICからDDSに変換する
	/// </summary>
	void ConvertTextureWICToDDS(const std::string& filePath);

private:
	/// <summary>
	/// フォルダパスとファイル名を分離する
	/// </summary>
	/// <param name="filePath"></param>
	void SeparateFilePath(const std::wstring& filePath);
	/// <summary>
	/// マルチバイト文字列をワイド文字列に変換
	/// </summary>
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

	void LoadWICTextureFromFile(const std::string& filePath);

	//画像の情報
	DirectX::TexMetadata metadata_;
	//画像イメージのコンテナ
	DirectX::ScratchImage scratchImage_;
	//ディレクトリパス
	std::wstring directoryPath_;
	//ファイル名
	std::wstring fileName_;
	//ファイル拡張子
	std::wstring fileExt_;
};