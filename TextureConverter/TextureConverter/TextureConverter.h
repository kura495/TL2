#pragma once
#include <string>
#include <Windows.h>
#include "../../externals/DirectXTex/DirectXTex.h"

class TextureConverter {
public:
	/// <summary>
	/// テクスチャをWICからDDSに変換する
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void ConvertTextureWICToDDS(const std::string& filePath,int numOptions = 0,char* options[] = nullptr);
	/// <summary>
	///	使用方法を出力(表示)する
	/// </summary>
	static void OutputUsage();
private:
	/// <summary>
	/// DDSテクスチャとしてファイル書き出し
	/// </summary>
	void SaveDDSTextureToFile(int numOptions, char* options[]);
	/// <summary>
	/// フォルダパスとファイル名を割する
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void SeparateFilePath(const std::wstring& filePath);
	/// <summary>
	/// テクスチャファイル読み込み
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void LoadWICTextureFromFile(const std::string& filePath);
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

private:
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