#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <vector>

using namespace std;

#define eps 1.0e-9


template <class _Ty>
	void triangulate(vector <vector <_Ty> > &a, int &countSwaps)
	{
		countSwaps = 1;
		for (int i = 0; i < (int)a.size(); i++)
		{
			// seeking for the row with the maximal first element
			int im = i;
			for (int j = i + 1; j < (int)a.size(); j++)
				if (abs(a[j][i]) > abs(a[im][i]))
					im = j;
			if (abs(a[im][i]) < eps)
				continue;
			for (int k = 0; k < (int)a[0].size(); k++)
				swap (a[i][k], a[im][k]);
			countSwaps = - countSwaps * ((i != im) ? 1 : -1);
      
			// substracting that row from all other
			for (int j = i + 1; j < (int)a.size(); j++)
			{
				double q = (0.0 - a[j][i]) / a[i][i];
				for (int k = a[0].size() - 1; k >= i; k--)
					a[j][k] += q * a[i][k];
			}
		}

		return void();
	}

template <class _Ty>
	_Ty get_det(vector <vector <_Ty> > &a)
	{
		int countSwaps;
		vector <vector <_Ty> > t = a;
		triangulate <_Ty> (t, countSwaps);
		_Ty result = 1;
		for (int i = 0; i < (int)t.size(); i++)
			result *= t[i][i];
		return countSwaps * result;
	}

