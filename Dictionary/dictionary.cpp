#include "dictionary.h"

dictionary::dictionary() {
}

dictionary::dictionary(std::string filename) {
	std::ifstream myfile(filename);
	std::string line;
	int i = 0;
	while (std::getline(myfile, line)) {
		data.insertWord(line);
	/*	if (++i % 5000 == 0)
			std::cout << line << std::endl;*/
	}

}

//inserting a word into an array given a line and a word
void dictionary::search(std::string board, std::string word,int vecSize) {
	if (board == "               "||word=="")
		return;
	std::sort(word.begin(), word.end());
	std::reverse(word.begin(), word.end());

	//data.returnVector.clear();
	int num = 1;
	for (int i = 0; i < board.size(); ++i) {
		if (board[i] == ' ')
			++num;
		else if (num > 0) {
			data.search(word, board, i, num - 1, vecSize);
			num = 0;
		}
	}

}

//inserting a word into an array given a line and a word and the index where you should start
void dictionary::search(std::string board, std::string word, int index,int vecSize) {
	if (board == "               " || word == "")
		return;
	std::sort(word.begin(), word.end());
	std::reverse(word.begin(), word.end());
	//data.returnVector.clear();
	int num = 1;
	for (int i = 0; i < board.size(); ++i) {
		if (board[i] == ' ')
			++num;
		else {
			if (num > 0 && i == index) {
				data.search(word, board, i, num - 1, vecSize);
				return;
			}
			num = 0;
		}
	}

}

//checks if a word exists in an array
bool dictionary::check(std::string word) {
	return this->data.check(this->data.root, word);
}

void dictionary::selectAll(std::string word) {
	this->data.search(word);
}

//never mind it's just for test :D
void dictionary::test() {

	std::string s1, s2, s3, s4, word = "EEEE";
	s1 = "  all  loa    a b ";
	s2 = " all a  a  ca  ";
	s3 = "all  ";
	s4 = "a";
	/*this->data.search("alEEEEE");
	 for (int i = 0; i < data.returnVector.size(); ++i)
	 std::cout << data.returnVector[i].first.first << "  " << std::endl;
	 return;*/

	std::cout << "word 1" << std::endl;
	int vicSize = -1;
	search(s1, word,vicSize);
	for (int i = 0; i < data.returnVector.size(); ++i)
		std::cout << data.returnVector[i].first.first << "  "
		<< data.returnVector[i].second << "\\";
	std::cout << "word 2" << std::endl;
	search(s2, word, vicSize);
	for (int i = 0; i < data.returnVector.size(); ++i)
		std::cout << data.returnVector[i].first.first << "  "
		<< data.returnVector[i].second << "\\";
	std::cout << "word 3" << std::endl;
	search(s3, word, vicSize);
	for (int i = 0; i < data.returnVector.size(); ++i)
		std::cout << data.returnVector[i].first.first << "  "
		<< data.returnVector[i].second << "\\";
	std::cout << "word 4" << std::endl;
	search(s4, word, vicSize);
	for (int i = 0; i < data.returnVector.size(); ++i)
		std::cout << data.returnVector[i].first.first << "  "
		<< data.returnVector[i].second << "\\";
}
//cast int[][] to char[][]
vector<string> dictionary::cast(int board[15][15]) {
	vector<string> rvec;
	for (int i = 0; i < 15; ++i) {
		string s;
		for (int j = 0; j < 15; ++j) {
			int x=board[i][j];
			if(x>99)
				x-=100;
			if (x == -1)
				s += ' ';
			else
				s += (char)x + 97;
		}
		rvec.push_back(s);
	}
	return rvec;
}
std::string dictionary::convert(std::string word,bool rack) {
	std::string temp;

	for (int i = 0; i < word.length(); ++i)
		if (word[i] >= 'a'&&word[i]<='z')
			if (!rack)
				temp += word[i];
			else
				temp +='E';
		else
			temp += (char)(word[i] + 32);
	return temp;
}
std::string dictionary::smallize(std::string word)
{
		string temp="";
		for (int i = 0; i < word.size(); ++i)
			if (word[i] <= 'Z')
				temp += (char)((int)word[i] + 32);
			else
				temp += word[i];
		return temp;
}

std::string dictionary::reverse(std::string word,bool rack) {
	std::string temp;
	for (int i = 0; i < word.length(); ++i)
		if (word[i] <= 'Z'&&word[i] >='A' )
			if (!rack)
				temp += (char)(word[i] + 32);
			else
				temp += 'e';
		else
			temp += (char)(word[i] - 32);
	return temp;
}
//vector<pair<pair<string, string>, int>>
//execute
int dictionary::checkWord(int index, int index2, vector<string> row, string col)
{

	int k;
	int ind = -1;
	string newWord = "";
	for (k = data.returnVector[index].second; k < data.returnVector[index].second + data.returnVector[index].first.first.size(); ++k)
	{
		string s = "";
		string s1 = "";
		if (col[k] == ' ')
		{
			newWord += data.returnVector[index].first.first[k- data.returnVector[index].second];
			s1 = data.returnVector[index].first.first[k - data.returnVector[index].second];
			if (ind < 0)ind = k;

		}
		else
		{
			
			continue;
		}
		for (int i = index2 + 1; i < 15; ++i)
			if (row[k][i] != ' ')
				s += row[k][i];
			else
				break;
		string s2 = "";
		for (int i = index2 - 1; i >= 0; --i)
			if (row[k][i] != ' ')
				s2 = row[k][i];
			else
				break;
		if (s.size() > 0 || s2.size() > 0)
		{
			string s3 = smallize(s2 + s1 + s);
			if (!this->check(s3))
			{
				
				return 0;
			}
		}
	}
	this->data.returnVector[index].first.first = newWord;
	this->data.returnVector[index].second =ind;
	return 1;
}
void dictionary::checkOne(int index,int index2,string rack,vector<string> row,string col,int vecSize)
{ 
	if (data.returnVector[index].first.second.size() == rack.size()-1)
	{
		int k = 0;
		for (k = data.returnVector[index].second; k < data.returnVector[index].second + data.returnVector[index].first.first.size(); ++k)
		{

			if (col[k] == ' ')
			{

				break;

			}
		}
		row[data.returnVector[index].second][index2] = data.returnVector[index].first.first[k-data.returnVector[index].second];
		this->search(row[data.returnVector[index].second], data.returnVector[index].first.second, index2, vecSize);
		this->data.returnVector[index].first.first = data.returnVector[index].first.first[k - data.returnVector[index].second];
		this->data.returnVector[index].second = k;
	}
}
void dictionary::execute(Board& b, std::string rack,int vecSize) {
//cout<<rack<<endl;
    this->returnVec.clear();
	//get columns
	int cols[15][15];
	int board[15][15];
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			cols[i][j] = b.getBoardValue(j , i);
			board[i][j] = b.getBoardValue(i, j);
		}
	}
	std::vector<std::string> col = this->cast(cols);
	std::vector<std::string> rows = this->cast(board);
	rack = this->convert(rack,true);

	
	for (int i = 0; i < 15; ++i) {
		this->data.returnVector.clear();
		this->search(col[i], rack, vecSize);
		for (int j = 0; j < data.returnVector.size(); ++j)
		{
			if (checkWord(j, i, rows, col[i]) != 1)
				continue;
			
			checkOne(j, i, rack, rows, col[i], vecSize);
			returnVec.push_back(
				Move(data.returnVector[j].second, i, true,
					this->reverse(data.returnVector[j].first.first),
					this->reverse(data.returnVector[j].first.second,true)));
		}
		this->data.returnVector.clear();
		this->search(rows[i], rack, vecSize);
		
		for (int j = 0; j < data.returnVector.size(); ++j)
		{
			
			if (checkWord(j, i,col, rows[i]) != 1)
				continue;
			checkOne(j, i, rack, col, rows[i], vecSize);
			returnVec.push_back(
				Move(i, data.returnVector[j].second, false,
					this->reverse(data.returnVector[j].first.first),
					this->reverse(data.returnVector[j].first.second,true)));
		}
	}
}

vector<Move> dictionary::getVector() {
	return returnVec;
}

dictionary::~dictionary() {
}