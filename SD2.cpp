#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream f("mergeheap.in");
ofstream g("mergeheap.out");

class Nod {
public:
    int val;
    int rank;
    Nod* copil;
    Nod* frate;
    Nod() : val(0), rank(0), copil(nullptr), frate(nullptr) {}
    Nod(int _val = 0) : val(_val), rank(0), copil(nullptr), frate(nullptr) {}
};

class RankPairingHeap {
public:
    Nod* rad;
    Nod* merge(Nod* rad1, Nod* rad2) {
        if (rad1 == nullptr) 
            return rad2;
        if (rad2 == nullptr) 
            return rad1;
        if (rad1->val < rad2->val){
            auto aux = rad1;
            rad1 = rad2;
            rad2 = aux;
        }
        rad2->frate = rad1->copil;
        rad1->copil = rad2;
        rad1->rank++;
        return rad1;
    }
    Nod* mergeHeap(Nod* rad1) {
        if (rad1 == nullptr or rad1->frate == nullptr)
            return rad1;
        Nod* n1 = rad1;
        Nod* n2 = rad1->frate;
        Nod* urm = n2->frate;
        n1->frate = nullptr;
        n2->frate = nullptr;
        return merge(merge(n1, n2), mergeHeap(urm));
    }

    
    RankPairingHeap(int _val) {
        rad = new Nod(_val);
    }
    RankPairingHeap() : rad(nullptr) {}

    void mergeWithSelf(RankPairingHeap toMergeHeap) {
        if (rad == nullptr) {
            rad = toMergeHeap.rad;
            return;
        }
        if (toMergeHeap.rad == nullptr) 
            return;
        if (rad->val < toMergeHeap.rad->val) {
            auto aux= rad;
            rad = toMergeHeap.rad;
            toMergeHeap.rad = aux;
        }
        toMergeHeap.rad->frate = rad->copil;
        rad->copil = toMergeHeap.rad;
        toMergeHeap.rad = nullptr;
    }
    Nod* getRad() {
		return rad;
	}
    void setRad(Nod* _rad) {
        rad = _rad;
    }
    int maxVal() {
        return rad->val;
    }
};

RankPairingHeap R[102];

int main()
{
    int N,Q,x,y,m,opt;
    f >> N >> Q;
    for (int t = 1; t <= Q; t++) {
        f >> opt;
        if (opt == 1) {
            f >> m >> x;
            R[m].mergeWithSelf(RankPairingHeap(x));
        }
        if (opt == 2) {
            f >> m;
            g << R[m].maxVal() << '\n';
            Nod* ultRad = R[m].getRad();
            R[m].setRad(R[m].mergeHeap(R[m].getRad()->copil));
            delete ultRad;
        }
        if (opt == 3) {
            f >> x >> y;
            R[x].mergeWithSelf(R[y]);
            R[y].setRad(nullptr);
        }
    }
    return 0;
}
