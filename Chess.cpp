#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct chess {
	vector<string> m;
	chess() : m(vector<string>(8, string(8, ' '))) {}
};

istream & operator >> (istream & i, chess & ch) {
	ch = chess();
	for (int x = 0; x < 64;) {
		char c;
		i >> c;
		if(string("rnbqkpRNBQKP").find(c) != string::npos){
			ch.m[x / 8][x % 8] = c;
			++x;
		} else if('0' <= c && c <= '9') {
			x += c - '0';
		}
	}
	char n;
	string s;
	int h;
	i >> n >> s >> s >> h >> h;
	return i;
}

ostream & operator << (ostream & o, chess const & ch) {
	ifstream templ("template.svg");
	const string sh = "rnbqkp";
	const string lo[] = {"rook", "knight", "bishop", "queen", "king", "pawn"};
	for(;;) {
		string s;
		if (templ.eof())
			break;
		getline (templ, s);
		if (s.find("@") == string::npos) {
			o << s << endl;
			continue;
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				char cc = ch.m[i][j];
				if (cc == ' ')
					continue;
				char c;
				if('a' <= cc && cc <= 'z'){
					c = 'b';
				} else {
					c = 'w';
					cc += 'a' - 'A';
				}
				o << "\t\t\t<use x=\"" << j * 100 << "px\" y=\"" << i * 100 << "px\" xlink:href=\"#" << c << "_" << lo[sh.find(cc)] << "\"/>" << endl;
			}
		}
	}
	return o;
}

int main() {
	chess c;

	ifstream fin("field.txt");
	fin >> c;

	ofstream fout("field.svg");
	fout << c;
}