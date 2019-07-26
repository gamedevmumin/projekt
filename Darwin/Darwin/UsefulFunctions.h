#pragma once
#include <string>
#include <cctype>
/**
@param s string, ktory chcemy sprawdzic, czy jest liczba zmiennoprzecinkowa
@return true, jesli string jest liczba, false jesli nie jest
*/
bool isFloatingNumber(const std::string& s);

/**
@param s string, ktory chcemy sprawdzic, czy jest liczba
@return true, jesli string jest liczba, false jesli nie jest
*/
bool isNumber(const std::string& s);