#include "account.h"

void superInsert(vector<string>& vec, string& id, string& target)
{
	int i = 0;
	int idScore = score(id, target);

	if(vec.size() == 0)
	{
		vec.push_back(id);
		return;
	}

	for(i = vec.size() - 1; i >= 0; i--)
	{
		if(score(vec[i], target) < idScore || (score(vec[i], target) == idScore && vec[i] < id))
			break;
	}
	vec.insert(vec.begin() + i + 1, id);

	if(vec.size() > 10)		vec.erase(vec.begin() + 10, vec.end());
}

void Bank::transfer(string& login, string& target, int num)
{
	//clock_t begin = clock();
	int loglen = login.length();
	int logind = toIndex(login);
	itr = data[target.length() - 1][toIndex(target)].find(target);

	if(itr != data[target.length() - 1][toIndex(target)].end())
	{
		if(data[loglen - 1][logind][login].money >= num)
		{
			data[loglen - 1][logind][login].money -= num;
			itr -> second.money += num;

			record *rec_dest = new record;
			record *rec_sour = new record;

			rec_sour -> IO = TO;					rec_dest -> IO = FROM;
			rec_sour -> target = target;			rec_dest -> target = login;
			rec_sour -> cash = num;					rec_dest -> cash = num;
			rec_sour -> deleted = false;			rec_dest -> deleted = false;
			rec_sour -> counterpart = rec_dest;		rec_dest -> counterpart = rec_sour;
			rec_sour -> timeStamp = _time;          rec_dest -> timeStamp = _time;
			data[loglen - 1][logind][login].history.push_back(rec_sour);
			itr -> second.history.push_back(rec_dest);

			_time++;

			cout << "success, " << data[loglen - 1][logind][login].money << " dollars left in current account" << endl;
		}
		else
			cout << "fail, " << data[loglen - 1][logind][login].money << " dollars only in current account" << endl;
	}
	else
	{
		int tlen = target.length() - 1;
		int upperbound = (99 - tlen > tlen)? 99 - tlen : tlen;

		vector<string> seq;
		for(int i = 0; i < 62; i++)
			for(itr = data[tlen][i].begin(); itr != data[tlen][i].end(); itr++)
				superInsert(seq, itr -> second.ID, target);

		if(seq.size() == 10)
			upperbound = (upperbound < score(seq[9], target))? upperbound : score(seq[9], target);

		for(int i = 1; i <= upperbound; i++)
		{
			if(tlen + i <= 99 && tlen - i >= 0)
			{
				for(int index = 0; index < 62; index++)
				{
					for(itr = data[tlen + i][index].begin(); itr != data[tlen + i][index].end(); itr++)
						superInsert(seq, itr -> second.ID, target);
					for(itr = data[tlen - i][index].begin(); itr != data[tlen - i][index].end(); itr++)
						superInsert(seq, itr -> second.ID, target);
				}
			}
			else if(tlen + i > 99 && tlen - i >= 0)
			{
				for(int index = 0; index < 62; index++)
					for(itr = data[tlen - i][index].begin(); itr != data[tlen - i][index].end(); itr++)
						superInsert(seq, itr -> second.ID, target);
			}
			else if(tlen + i <= 99 && tlen - i < 0)
			{
				for(int index = 0; index < 62; index++)
					for(itr = data[tlen + i][index].begin(); itr != data[tlen + i][index].end(); itr++)
						superInsert(seq, itr -> second.ID, target);
			}
			
			if(seq.size() == 10)
				upperbound = (upperbound < score(seq[9], target))? upperbound : score(seq[9], target);
		}

		cout << "ID " << target << " not found, ";
		if(seq.size() == 0) return;
		else
		{
			for(int i = 0; i < seq.size() - 1; i++)
				cout << seq[i] << ",";
			cout << seq[seq.size() - 1] << endl;
		}
	}

	//clock_t end = clock();
	//cout << "Trans Ex Time = " << ((double)end - begin) / CLOCKS_PER_SEC << endl;
}
