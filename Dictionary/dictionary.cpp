#include "dictionary.h"



dictionary::dictionary()
{
}

dictionary::dictionary(std::string filename)
{
	std::ifstream myfile(filename);
	std::string line;
	int i = 0;
	while (std::getline(myfile, line))
	{
		data.insertWord(line);
		if (++i % 5000 == 0) std::cout << line << std::endl;
	}
	
}

//inserting a word into an array given a line and a word
void dictionary::search(std::string board, std::string word)
{
	std::sort(word.begin(), word.end());
	std::reverse(word.begin(), word.end());

	data.returnVector.clear();
	int num = 1;
	for (int i = 0; i < board.size(); ++i)
	{
		if (board[i] == ' ')
			++num;
		else
			if (num > 0)
			{
				data.search(word, board, i, num - 1);
				num = 0;
			}
	}
}

//inserting a word into an array given a line and a word and the index where you should start
void dictionary::search(std::string board, std::string word,int index)
{
	std::sort(word.begin(), word.end());
	std::reverse(word.begin(), word.end());
	data.returnVector.clear();
	int num = 1;
	for (int i = 0; i < board.size(); ++i)
	{
		if (board[i] == ' ')
			++num;
		else
		{
			if (num > 0 && i == index)
			{
				data.search(word, board, i, num - 1);
				return;
			}
			num = 0;
		}
	}
}

//checks if a word exists in an array
bool dictionary::check(std::string word)
{
	return this->data.check(this->data.root, word);
}

void dictionary::selectAll(std::string word)
{
	this->data.search(word);
}

//never mind it's just for test :D
void dictionary::test()
{

	std::string s1, s2, s3, s4,word="EEEE";
	s1 = "  all  loa    a b ";
	s2 = " all a  a  ca  ";
	s3 = "all  ";
	s4 = "a";
	/*this->data.search("alEEEEE");
	for (int i = 0; i < data.returnVector.size(); ++i)
		std::cout << data.returnVector[i].first.first << "  " << std::endl;
	return;*/

	std::cout << "word 1" << std::endl;
	search(s1, word);
	for (int i = 0; i < data.returnVector.size(); ++i)
		std::cout << data.returnVector[i].first.first << "  " << data.returnVector[i].second << "\\";
	std::cout << "word 2" << std::endl;
	search(s2, word);
	for (int i = 0; i < data.returnVector.size(); ++i)
		std::cout << data.returnVector[i].first.first << "  " << data.returnVector[i].second << "\\";
	std::cout << "word 3" << std::endl;
	search(s3, word);
	for (int i = 0; i < data.returnVector.size(); ++i)
		std::cout << data.returnVector[i].first.first << "  " << data.returnVector[i].second << "\\";
	std::cout << "word 4" << std::endl;
	search(s4, word);
	for (int i = 0; i < data.returnVector.size(); ++i)
		std::cout << data.returnVector[i].first.first << "  " << data.returnVector[i].second << "\\";
}
//cast int[][] to char[][]
vector<string> dictionary::cast(int board[15][15])
{
	vector<string> rvec;
	for (int i = 0; i < 15; ++i)
	{
		string s;
		for (int j = 0; i < 15; ++j)
		{
			if (board[i][j] == 0)
				s += ' ';
			else
				s +=(char) board[i][j] + 97;
		}
		rvec.push_back(s);
	}
	return rvec;
}
std::string dictionary::convert(std::string word)
{
	std::string temp;
	for (int i = 0; i < word.length(); ++i)
		if (word[i] == 'e')
			temp += 'E';
		else 
			temp += (char)(word[i]+27);
	return temp;
}
std::string dictionary::reverse(std::string word)
{
	std::string temp;
	for (int i = 0; i < word.length(); ++i)
		if (word[i] == 'E')
			temp += 'e';
		else
			temp += (char)(word[i] - 27);
	return temp;
}
//vector<pair<pair<string, string>, int>>
//execute
void dictionary::execute(int board[15][15],std::string rack)
{

	//get columns
	int cols[15][15];
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			cols[i][j] = board[j][i];
		}
	}
	std::vector<std::string> col = this->cast(cols);
	std::vector<std::string> rows = this->cast(board);
	rack=this->convert(rack);
	
	for (int i = 0; i < 15; ++i)
	{
		this->search(col[i], rack);
		for (int j = 0; j < data.returnVector.size(); ++j)
			returnVec.push_back(Move(data.returnVector[j].second,i,true,this->reverse(data.returnVector[j].first.first),this->reverse(data.returnVector[j].first.second)));

		this->search(rows[i], rack);
		for (int j = 0; j < data.returnVector.size(); ++j)
			returnVec.push_back(Move(i,data.returnVector[j].second,false,this->reverse(data.returnVector[j].first.first),this->reverse(data.returnVector[j].first.second)));
	}
}










dictionary::~dictionary()
{
}
