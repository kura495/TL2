#pragma once
#include <string>
#include <Windows.h>
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
	/// マルチバイト文字列をワイド文字列に変換
	/// </summary>
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

	void LoadWICTextureFromFile(const std::string& filePath);
};