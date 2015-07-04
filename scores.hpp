#ifndef SCORES_HPP
#define SCORES_HPP

class Score {
	int scores[14];
	int head;
public:
	Score();
	void filewrite();
	void fileread();
	void addscore(int s);
	void sortscore(void);
	void Render(void);
	int gethead(void);
};

#endif
