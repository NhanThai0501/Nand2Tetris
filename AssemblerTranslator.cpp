#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

string AinstructionDecode(string instructionA);
string CinstructionDecode(string instructionC); 
int checkSymbol(vector<string>& symbols, string s);
int checkNum(string num); 
string integerToString(int i);

int main()
{
	vector<string> symbols;
	map<string, int> SymbolTable;

	string asmFile = "Add.asm";
	ifstream readFile(asmFile);
	string file = asmFile;
	int dot = file.find(".", 0);
	string hackFile = file.substr(0, dot) + ".hack";
	ofstream writeFile(hackFile.c_str());

	SymbolTable["R0"] = 0;
	SymbolTable["R1"] = 1;
	SymbolTable["R2"] = 2;
	SymbolTable["R3"] = 3;
	SymbolTable["R4"] = 4;
	SymbolTable["R5"] = 5;
	SymbolTable["R6"] = 6;
	SymbolTable["R7"] = 7;
	SymbolTable["R8"] = 8;
	SymbolTable["R9"] = 9;
	SymbolTable["R10"] = 10;
	SymbolTable["R11"] = 11;
	SymbolTable["R12"] = 12;
	SymbolTable["R13"] = 13;
	SymbolTable["R14"] = 14;
	SymbolTable["R15"] = 15;
	SymbolTable["SCREEN"] = 16384;
	SymbolTable["KBD"] = 24576;
	SymbolTable["SP"] = 0;
	SymbolTable["LCL"] = 1;
	SymbolTable["ARG"] = 2;
	SymbolTable["THIS"] = 3;
	SymbolTable["THAT"] = 4;
	
	symbols.push_back("R0");
	symbols.push_back("R1");
	symbols.push_back("R2");
	symbols.push_back("R3");
	symbols.push_back("R4");
	symbols.push_back("R5");
	symbols.push_back("R6");
	symbols.push_back("R7");
	symbols.push_back("R8");
	symbols.push_back("R9");
	symbols.push_back("R10");
	symbols.push_back("R11");
	symbols.push_back("R12");
	symbols.push_back("R13");
	symbols.push_back("R14");
	symbols.push_back("R15");
	symbols.push_back("SCREEN");
	symbols.push_back("KBD");
	symbols.push_back("SP");
	symbols.push_back("LCL");
	symbols.push_back("ARG");
	symbols.push_back("THIS");
	symbols.push_back("THAT");

	int symbolSize = 22;

	
	int PC = 0;
	int RAM_index = 16;
	string sym;
	while (getline(readFile, sym))
	{
		if ((sym.substr(0, 1) == "(") && !(checkSymbol(symbols, sym.substr(1, sym.find(")", 0) - 1))))
		{
			SymbolTable[sym.substr(1, sym.find(")", 0) - 1)] = PC;
			symbols.push_back(sym.substr(1, sym.find(")", 0) - 1));
			symbolSize++;
		}
		if (sym.substr(0, 1) != "/" && sym.substr(0, 1) != "(" && sym.substr(0, 1) != "")
			PC++;
	}
	readFile.close();
	
	readFile.open(asmFile);
	while (getline(readFile, sym))
	{
		if (sym.substr(0, 1) == "@")
		{
			if (!(checkNum(sym.substr(1, 1))) && !(checkSymbol(symbols, sym.substr(1, sym.find(" ", 0) - 1))))
			{
				SymbolTable[sym.substr(1, sym.length() - 1)] = RAM_index;
				RAM_index++;
				symbols.push_back(sym.substr(1, sym.length() - 1));
				symbolSize++;
			}
		}
	}
	readFile.close();

	
	string command, hack_command;
	readFile.open(asmFile); 
	while (getline(readFile, command))
	{
		if (command.substr(0, 1) == "/" || command.substr(0, 1) == "" || command.substr(0, 1) == "(") 
		{
			continue;
		}
		else if (command.substr(0, 1) == "@") 
		{
			if (checkNum(command.substr(1, 1)))
			{
				hack_command = AinstructionDecode(command.substr(1, command.length() - 1));
				writeFile << hack_command << endl;
			}
			else 
			{
				hack_command = AinstructionDecode(integerToString(SymbolTable[command.substr(1, command.length() - 1)]));
				writeFile << hack_command << endl;
			}
		}
		else 
		{
			hack_command = CinstructionDecode(command);
			writeFile << hack_command << endl;
		}
	}

	readFile.close();
	writeFile.close();

	readFile.open(hackFile.c_str());
	string hackLine;
	int line = 1;
	while (getline(readFile, hackLine))
	{
		if (hackLine.length() != 16)
			cout << "Error in line " << line << " Please correct your syntax in .asm file." << endl;
		line++;
	}
	readFile.close();
	return 0;
}

	string AinstructionDecode(string instructionA) 
	{
		int value = stoi(instructionA);
		string result = "0";
		if ((value - 16384) >= 0)
		{
			value -= 16384;
			result += "1";
		}
		else
			result += "0";
		if ((value - 8192) >= 0)
		{
			value -= 8192;
			result += "1";
		}
		else
			result += "0";
		if ((value - 4096) >= 0)
		{
			value -= 4096;
			result += "1";
		}
		else
			result += "0";
		if ((value - 2048) >= 0)
		{
			value -= 2048;
			result += "1";
		}
		else
			result += "0";
		if ((value - 1024) >= 0)
		{
			value -= 1024;
			result += "1";
		}
		else
			result += "0";
		if ((value - 512) >= 0)
		{
			value -= 512;
			result += "1";
		}
		else
			result += "0";
		if ((value - 256) >= 0)
		{
			value -= 256;
			result += "1";
		}
		else
			result += "0";
		if ((value - 128) >= 0)
		{
			value -= 128;
			result += "1";
		}
		else
			result += "0";
		if ((value - 64) >= 0)
		{
			value -= 64;
			result += "1";
		}
		else
			result += "0";
		if ((value - 32) >= 0)
		{
			value -= 32;
			result += "1";
		}
		else
			result += "0";
		if ((value - 16) >= 0)
		{
			value -= 16;
			result += "1";
		}
		else
			result += "0";
		if ((value - 8) >= 0)
		{
			value -= 8;
			result += "1";
		}
		else
			result += "0";
		if ((value - 4) >= 0)
		{
			value -= 4;
			result += "1";
		}
		else
			result += "0";
		if ((value - 2) >= 0)
		{
			value -= 2;
			result += "1";
		}
		else
			result += "0";
		if ((value - 1) >= 0)
		{
			value -= 1;
			result += "1";
		}
		else
			result += "0";
		return result;
	}

	string CinstructionDecode(string instructionC) 
	{
		instructionC = instructionC.substr(0, instructionC.find(" ", 0));
		string result = "111";
		string comp, dest, jump;
		
		int equalSign = instructionC.find("=", 0);
		if (equalSign > -1 && equalSign < instructionC.length())
		{
			if (instructionC.substr(equalSign + 1, 3) == "D|M")
				comp = "1010101";
			else if (instructionC.substr(equalSign + 1, 3) == "D|A")
				comp = "0010101";
			else if (instructionC.substr(equalSign + 1, 3) == "D&A")
				comp = "0000000";
			else if (instructionC.substr(equalSign + 1, 3) == "D&M")
				comp = "1000000";
			else if (instructionC.substr(equalSign + 1, 3) == "A-D")
				comp = "0000111";
			else if (instructionC.substr(equalSign + 1, 3) == "M-D")
				comp = "1000111";
			else if (instructionC.substr(equalSign + 1, 3) == "D+1")
				comp = "0011111";
			else if (instructionC.substr(equalSign + 1, 3) == "A+1")
				comp = "0110111";
			else if (instructionC.substr(equalSign + 1, 3) == "M+1")
				comp = "1110111";
			else if (instructionC.substr(equalSign + 1, 3) == "D-1")
				comp = "0001110";
			else if (instructionC.substr(equalSign + 1, 3) == "A-1")
				comp = "0110010";
			else if (instructionC.substr(equalSign + 1, 3) == "M-1")
				comp = "1110010";
			else if (instructionC.substr(equalSign + 1, 3) == "D+A")
				comp = "0000010";
			else if (instructionC.substr(equalSign + 1, 3) == "D+M")
				comp = "1000010";
			else if (instructionC.substr(equalSign + 1, 3) == "D-A")
				comp = "0010011";
			else if (instructionC.substr(equalSign + 1, 3) == "D-M")
				comp = "1010011";
			else if (instructionC.substr(equalSign + 1, 2) == "-1")
				comp = "0111010";
			else if (instructionC.substr(equalSign + 1, 2) == "!D")
				comp = "0001101";
			else if (instructionC.substr(equalSign + 1, 2) == "!A")
				comp = "0110001";
			else if (instructionC.substr(equalSign + 1, 2) == "!M")
				comp = "1110001";
			else if (instructionC.substr(equalSign + 1, 2) == "-D")
				comp = "0001111";
			else if (instructionC.substr(equalSign + 1, 2) == "-A")
				comp = "0110011";
			else if (instructionC.substr(equalSign + 1, 2) == "-M")
				comp = "1110011";
			else if (instructionC.substr(equalSign + 1, 1) == "0")
				comp = "0101010";
			else if (instructionC.substr(equalSign + 1, 1) == "1")
				comp = "0111111";
			else if (instructionC.substr(equalSign + 1, 1) == "D")
				comp = "0001100";
			else if (instructionC.substr(equalSign + 1, 1) == "A")
				comp = "0110000";
			else if (instructionC.substr(equalSign + 1, 1) == "M")
				comp = "1110000";
		}
		else
		{
			if (instructionC.find("D|M", 0) >= 0 && instructionC.find("D|M", 0) < instructionC.length())
				comp = "1010101";
			else if (instructionC.find("D|A", 0) >= 0 && instructionC.find("D|A", 0) < instructionC.length())
				comp = "0010101";
			else if (instructionC.find("D&A", 0) >= 0 && instructionC.find("D&A", 0) < instructionC.length())
				comp = "0000000";
			else if (instructionC.find("D&M", 0) >= 0 && instructionC.find("D&M", 0) < instructionC.length())
				comp = "1000000";
			else if (instructionC.find("A-D", 0) >= 0 && instructionC.find("A-D", 0) < instructionC.length())
				comp = "0000111";
			else if (instructionC.find("M-D", 0) >= 0 && instructionC.find("M-D", 0) < instructionC.length())
				comp = "1000111";
			else if (instructionC.find("D+1", 0) >= 0 && instructionC.find("D+1", 0) < instructionC.length())
				comp = "0011111";
			else if (instructionC.find("A+1", 0) >= 0 && instructionC.find("A+1", 0) < instructionC.length())
				comp = "0110111";
			else if (instructionC.find("M+1", 0) >= 0 && instructionC.find("M+1", 0) < instructionC.length())
				comp = "1110111";
			else if (instructionC.find("D-1", 0) >= 0 && instructionC.find("D-1", 0) < instructionC.length())
				comp = "0001110";
			else if (instructionC.find("A-1", 0) >= 0 && instructionC.find("A-1", 0) < instructionC.length())
				comp = "0110010";
			else if (instructionC.find("M-1", 0) >= 0 && instructionC.find("M-1", 0) < instructionC.length())
				comp = "1110010";
			else if (instructionC.find("D+A", 0) >= 0 && instructionC.find("D+A", 0) < instructionC.length())
				comp = "0000010";
			else if (instructionC.find("D+M", 0) >= 0 && instructionC.find("D+M", 0) < instructionC.length())
				comp = "1000010";
			else if (instructionC.find("D-A", 0) >= 0 && instructionC.find("D-A", 0) < instructionC.length())
				comp = "0010011";
			else if (instructionC.find("D-M", 0) >= 0 && instructionC.find("D-M", 0) < instructionC.length())
				comp = "1010011";
			else if (instructionC.find("-1", 0) >= 0 && instructionC.find("-1", 0) < instructionC.length())
				comp = "0111010";
			else if (instructionC.find("!D", 0) >= 0 && instructionC.find("!D", 0) < instructionC.length())
				comp = "0001101";
			else if (instructionC.find("!A", 0) >= 0 && instructionC.find("!A", 0) < instructionC.length())
				comp = "0110001";
			else if (instructionC.find("!M", 0) >= 0 && instructionC.find("!M", 0) < instructionC.length())
				comp = "1110001";
			else if (instructionC.find("-D", 0) >= 0 && instructionC.find("-D", 0) < instructionC.length())
				comp = "0001111";
			else if (instructionC.find("-A", 0) >= 0 && instructionC.find("-A", 0) < instructionC.length())
				comp = "0110011";
			else if (instructionC.find("-M", 0) >= 0 && instructionC.find("-M", 0) < instructionC.length())
				comp = "1110011";
			else if (instructionC.find("0", 0) >= 0 && instructionC.find("0", 0) < instructionC.length())
				comp = "0101010";
			else if (instructionC.find("1", 0) >= 0 && instructionC.find("1", 0) < instructionC.length())
				comp = "0111111";
			else if (instructionC.find("D", 0) >= 0 && instructionC.find("D", 0) < instructionC.length())
				comp = "0001100";
			else if (instructionC.find("A", 0) >= 0 && instructionC.find("A", 0) < instructionC.length())
				comp = "0110000";
			else if (instructionC.find("M", 0) >= 0 && instructionC.find("M", 0) < instructionC.length())
				comp = "1110000";
		}
		
		int semicolonSymbol = instructionC.find(";", 0);
		if (instructionC.substr(semicolonSymbol + 1, 3) == "JGT")
			jump = "001";
		else if (instructionC.substr(semicolonSymbol + 1, 3) == "JEQ")
			jump = "010";
		else if (instructionC.substr(semicolonSymbol + 1, 3) == "JGE")
			jump = "011";
		else if (instructionC.substr(semicolonSymbol + 1, 3) == "JLT")
			jump = "100";
		else if (instructionC.substr(semicolonSymbol + 1, 3) == "JNE")
			jump = "101";
		else if (instructionC.substr(semicolonSymbol + 1, 3) == "JLE")
			jump = "110";
		else if (instructionC.substr(semicolonSymbol + 1, 3) == "JMP")
			jump = "111";
		else
			jump = "000";
	
		if (equalSign > -1 && equalSign < instructionC.length())
		{
			string d1, d2, d3;
			int findM = instructionC.find("M", 0);
			if (findM > -1 && findM < equalSign)
				d3 = "1";
			else
				d3 = "0";
			int findD = instructionC.find("D", 0);
			if (findD > -1 && findD < equalSign)
				d2 = "1";
			else
				d2 = "0";
			int findA = instructionC.find("A", 0);
			if (findA > -1 && findA < equalSign)
				d1 = "1";
			else
				d1 = "0";
			dest = d1 + d2 + d3;
		}
		else
			dest = "000"; 
		result = result + comp + dest + jump;
		return result;
	}

	int checkSymbol(vector<string>& symbols, string s)
	{
		for (int i = 0; i < symbols.size(); i++)
			if (symbols[i] == s)
				return 1;
		return 0;
	}

	int checkNum(string num) 
	{
		if (num == "0" || num == "1" || num == "2" || num == "3" || num == "4" || num == "5" || num == "6" || num == "7" || num == "8" || num == "9")
			return 1;
		else
			return 0;
	}

	string integerToString(int i) 
	{
		ostringstream s;
		s << i;
		return s.str();
	}
