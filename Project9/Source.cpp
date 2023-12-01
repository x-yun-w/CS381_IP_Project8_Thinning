#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class Thinning {
public:
	int numR;
	int numC;
	int minV;
	int maxV;
	int changeC;
	int cycleC;
	int** aryOne;
	int** aryTwo;
	int nAry[9];

public:
	Thinning(int r,int c, int mi, int ma) {
		numR = r;
		numC = c;
		minV = mi;
		maxV = ma;
		aryOne = new int* [numR + 2];
		aryTwo = new int* [numR + 2];
		for (int j = 0; j < numR + 2; j++) {
			aryOne[j] = new int[numC + 2];
			aryTwo[j] = new int[numC + 2];
		}

		for (int i = 0; i < numR + 2; i++) {
			for (int j = 0; j < numC + 2; j++) {
				aryOne[i][j] = 0;
				aryTwo[i][j] = 0;
			}
		}
	}

	void zeroFraming() {
		for (int i = 0; i < numC + 1; i++) {
			aryOne[0][i] = 0;
			aryOne[numR + 1][i] = 0; 
			aryTwo[0][i] = 0;
			aryTwo[numR + 1][i] = 0;
		}

		for (int i = 0; i <= numR + 1; i++) {
			aryOne[i][0] = 0;
			aryOne[i][numC + 1] =0;
			aryTwo[i][0] = 0;
			aryTwo[i][numC + 1] = 0;
		}
	}

	void loadImage(ifstream& in) {
		for (int i = 1; i < numR + 1; i++) {
			for (int j = 1; j < numC + 1; j++) {
				in >> aryOne[i][j];
				
			}
		}
	}

	int loadNeighborAry(int i, int j, ofstream& de) {
		int c = 0;
		int z = 0;
		
		for (int x = i - 1; x < i + 2; x++) {
			for (int y = j - 1; y < j + 2; y++) {
				nAry[z] = aryOne[x][y];
				if (nAry[z] > 0)
					c++;
				z++;
			}
		}
		return c - 1;
	}

	void copyAry() {

		for (int i = 1; i < numR + 1; i++) {
			for (int j = 1; j < numC + 1; j++) {
				aryOne[i][j]= aryTwo[i][j];
			}
		}
	}

	void thinning(ofstream& de) {
		de << "\nEntering thinning () before thinning 4 sides, aryOne is below:";
		imgReformat(aryOne, ".", de);
		changeC = 0;
		
		northThinning(de);
		de << "\nafter northThinning; aryTwo is below: ";
		imgReformat(aryTwo, ".", de);
		copyAry();

		southThinning(de);
		de << "\nafter southThinning; aryTwo is below: ";
		imgReformat(aryTwo, ".", de);
		copyAry();

		westThinning(de);
		de << "\nafter westThinning; aryTwo is below: ";
		imgReformat(aryTwo, ".", de);
		copyAry();

		eastThinning(de);
		de << "\nafter eastThinning; aryTwo is below: ";
		imgReformat(aryTwo, ".", de);
		copyAry();

		de << "\nLeaving thinning (); cycleCount = " << cycleC << "; changeCount = " << changeC <<";"<< endl;
	}

	void northThinning(ofstream& de) {
		de << "\nEntering northThinning (); cycleCount = " << cycleC << "; changeCount = " << changeC << ";" << endl;
		int i = 1;
		
		int nonZeroCount=0;
		bool flag=false;
		zeroFraming();
		while(i<numR+2)
		{
			int j = 1;
			while (j < numC + 2)
			{
				if (aryOne[i][j] > 0 && aryOne[i - 1][j] == 0) {
					nonZeroCount = loadNeighborAry(i, j, de);
					flag = checkConnector();
					de << "In northThinning, i= " << i << "; j = " << j << "; nonZeroCount = " << nonZeroCount << "; flag = " << flag << endl;
				}
				if (nonZeroCount >= 4 && !flag) {
					aryTwo[i][j] = 0;
					changeC++;
				}
				else {
					aryTwo[i][j] = aryOne[i][j]; 
				}
				j++;
			}
			i++;
		}

		de<< "\nLeaving northThinning (); cycleCount = " << cycleC << "; changeCount = " << changeC << ";" << endl;
	}

	void southThinning(ofstream& de) {
		de << "\nEntering southThinning (); cycleCount = " << cycleC << "; changeCount = " << changeC << ";" << endl;
		int i = 1;
		int nonZeroCount = 0;
		bool flag = false;
		while (i < numR + 2)
		{
			int j = 1;
			while (j < numC + 2)
			{
				if (aryOne[i][j] > 0 && aryOne[i + 1][j] == 0) {
					nonZeroCount = loadNeighborAry(i, j, de);
					flag = checkConnector();
					de << "In southThinning, i= " << i << "; j = " << j << "; nonZeroCount = " << nonZeroCount << "; flag = " << flag << endl;
				}
				if (nonZeroCount >= 4 && !flag) {
					aryTwo[i][j] = 0;
					changeC++;
				}
				else {
					aryTwo[i][j] = aryOne[i][j];
				}
				j++;
			}
			i++;
		}

		de << "\nLeaving southThinning (); cycleCount = " << cycleC << "; changeCount = " << changeC << ";" << endl;
	}

	void westThinning(ofstream& de) {
		de << "\nEntering westThinning (); cycleCount = " << cycleC << "; changeCount = " << changeC << ";" << endl;
		int i = 1;
		int nonZeroCount = 0;
		bool flag = false;
		while (i < numR + 2)
		{
			int j = 1;
			while (j < numC + 2)
			{
				if (aryOne[i][j] > 0 && aryOne[i][j-1] == 0) {
					nonZeroCount = loadNeighborAry(i, j, de);
					flag = checkConnector();
					de << "In westThinning, i= " << i << "; j = " << j << "; nonZeroCount = " << nonZeroCount << "; flag = " << flag << endl;
				}
				if (nonZeroCount >= 4 && !flag) {
					aryTwo[i][j] = 0;
					changeC++;
				}
				else {
					aryTwo[i][j] = aryOne[i][j];
				}
				j++;
			}
			i++;
		}

		de << "\nLeaving westThinning (); cycleCount = " << cycleC << "; changeCount = " << changeC << ";" << endl;
	}

	void eastThinning(ofstream& de) {
		de << "\nEntering eastThinning (); cycleCount = " << cycleC << "; changeCount = " << changeC << ";" << endl;
		int i = 1;
		int nonZeroCount=0;
		bool flag=false;
		while (i < numR + 2)
		{
			int j = 1;
			while (j < numC + 2)
			{
				if (aryOne[i][j] > 0 && aryOne[i ][j+1] == 0) {
					nonZeroCount = loadNeighborAry(i, j,de);
					flag = checkConnector();
					de << "In eastThinning, i= " << i << "; j = " << j << "; nonZeroCount = " << nonZeroCount << "; flag = " << flag << endl;
				}
				if (nonZeroCount >= 4 && !flag) {
					aryTwo[i][j] = 0;
					changeC++;
				}
				else {
					aryTwo[i][j] = aryOne[i][j];
				}
				j++;
			}
			i++;
		}

		de << "\nLeaving eastThinning (); cycleCount = " << cycleC << "; changeCount = " << changeC << ";" << endl;
	}

	bool checkConnector() {
		return (nAry[1] == 0 && nAry[7] == 0) ||
			(nAry[3] == 0 && nAry[5] == 0) ||
			(nAry[0] == 1 && nAry[1] == 0 && nAry[3] == 0) ||
			(nAry[2] == 1 && nAry[1] == 0 && nAry[5] == 0) ||
			(nAry[6] == 1 && nAry[3] == 0 && nAry[7] == 0) ||
			(nAry[8] == 1 && nAry[5] == 0 && nAry[7] == 0);
	}

	void imgReformat(int** inAry, string d, ofstream& out) {
		out << numR << " " << numC << " " << minV << " " << maxV << endl;
		string s = to_string(maxV);

		int w = s.length();
		int r = 0;
		while (r <= numR +1) {
			int c = 0;
			while (c <= numC + 1) {
				if (inAry[r][c] == 0) {
					out << d;
				}
				else {
					out << inAry[r][c];
				}
				s = to_string(inAry[r][c]);
				int ww = s.length();
				while (ww <= w) {
					out << " ";
					ww++;
				}
				c++;
			}
			out << endl;
			r++;
		}
	}
};

int main(int argc, char* argv[]) {
	ifstream in(argv[1]);
	ofstream out(argv[2]);
	ofstream debug(argv[3]);
	int r, c, n, m;
	
	in >> r>>c>>n>>m;
	Thinning t =Thinning(r, c, n, m);
	out << t.numR << " " << t.numC << " " << t.minV << " " << t.maxV << endl;
	t.changeC = 0;
	t.cycleC = 0;
	
	t.loadImage(in);

	out<<"\nIn main (), before thinning; changeCount= " << t.changeC << "; cycleCount = " << t.cycleC << ";" << endl;
	t.imgReformat(t.aryOne, ".", out);
	do
	{
		t.thinning(debug);
		t.cycleC++;

		out << "\nIn main (), inside iteration; changeCount= " << t.changeC << "; cycleCount = " << t.cycleC << ";" << endl;
		t.imgReformat(t.aryOne, ".", out);
	} while (t.changeC > 0);
	out << "\nIn main (), the final skeleton; changeCount= " << t.changeC << "; cycleCount = " << t.cycleC << ";" << endl;
	t.imgReformat(t.aryOne, "0", out);

	in.close();
	out.close();
	debug.close();
};