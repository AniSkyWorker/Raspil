#include "stdafx.h"

class CCutsAggregator
{
public:
	CCutsAggregator() = default;
	~CCutsAggregator() = default;

	void InitFromFile(const std::string & fileName)
	{
		std::ifstream in(fileName);
		in >> m_lumberLength;
		in >> m_cutsCount;

		m_cutPlaces.push_back(0);
		for (size_t i = 0; i < m_cutsCount; i++)
		{
			int cut;
			in >> cut;
			m_cutPlaces.push_back(cut);
		}
		m_cutPlaces.push_back(m_lumberLength);
	}

	void WriteResultInFile(const std::string & fileName)
	{
		std::ofstream out(fileName);
		out << GetMinCutsPrice();
	}

private:
	int GetMinCutsPrice()
	{
		boost::numeric::ublas::matrix<int> cutsMatrix(m_cutsCount + 2, m_cutsCount + 2, 0);

		for (size_t d = 2; d < m_cutsCount + 2; d++)
		{
			for (size_t i = 0; i < m_cutsCount + 2 - d; i++)
			{
				int min = INT_MAX;
				for (size_t k = i + 1; k < i + d; k++)
				{
					auto cur = cutsMatrix(i, k) + cutsMatrix(k, i + d);
					if (cur < min)
					{
						min = cur;
					}
					//min = cur < min ? cur : min;
				}
				cutsMatrix(i, i + d) = m_cutPlaces[i + d] - m_cutPlaces[i] + min;
			}
		}

		return cutsMatrix(0, m_cutsCount + 1);
	}

	int m_lumberLength;
	size_t m_cutsCount;
	std::vector<int> m_cutPlaces;
};
int main()
{
	CCutsAggregator cuts;
	cuts.InitFromFile("input1.txt");
	cuts.WriteResultInFile("output.txt");
    return 0;
}

