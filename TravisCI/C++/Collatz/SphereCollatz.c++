/** \file Collatz.c++
 *   Main Collatz file containing.
 *  Without the worlds end.
 */


/*! \mainpage CS378 Collatz
 *
 * \section intro_sec Introduction
 *
 *
 * "Background:
 * Problems in Computer Science are often classified as
 * belonging to a certain class of problems (e.g., NP,
 * Unsolvable, Recursive). In this problem you will be
 * analyzing a property of an algorithm whose classification
 * is not known for all possible inputs."
 * http://www.spoj.com/problems/PROBTNPO/
 * \section time_est Time
 * Estimate: 6 hours
 * Actual: 12 hours
 *
 * \section install_sec The Problem
 * Consider the following algorithm:
 * 1. input n
 * 2. print n
 * 3. if n = 1 then STOP
 *         4. if n is odd then n = 3n + 1
 *
 *          5. else n = n / 2
 * 6. GOTO 2
 * Given the input 22, the following sequence of numbers will be printed 22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1
 *
 * It is conjectured that the algorithm above will terminate (when a 1 is printed) for any integral input value. Despite the simplicity of the algorithm, it is unknown whether this conjecture is true. It has been verified, however, for all integers n such that 0 < n < 1,000,000 (and, in fact, for many more numbers than this.)
 *
 * Given an input n, it is possible to determine the number of numbers printed (including the 1). For a given n this is called the cycle-length of n. In the example above, the cycle length of 22 is 16.
 *
 * For any two numbers i and j you are to determine the maximum cycle length over all numbers between i and j.
 *
 *
 */


// --------
// includes
// --------


#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <map>

using namespace std;

// ------------
// collatz_read
// ------------

 pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);
}

/**
 * @mini_cache1
 * 500 interval -> 50,000
 */

std::map <pair<int,int>,int> mini_cache1;

/**
 * @mini_cache2
 * 100 interval -> 10,000
 */

std::map <pair<int,int>,int> mini_cache2;

/**
 * @collatz_cache
 * Configures the static cache for 100, 500 intervals
 */
 
 void collatz_cache(){
    mini_cache1.insert(make_pair(make_pair(1,100),119));
    mini_cache1.insert(make_pair(make_pair(101,200),125));
    mini_cache1.insert(make_pair(make_pair(201,300),128));
    mini_cache1.insert(make_pair(make_pair(301,400),144));
    mini_cache1.insert(make_pair(make_pair(401,500),142));
    mini_cache1.insert(make_pair(make_pair(501,600),137));
    mini_cache1.insert(make_pair(make_pair(601,700),145));
    mini_cache1.insert(make_pair(make_pair(701,800),171));
    mini_cache1.insert(make_pair(make_pair(801,900),179));
    mini_cache1.insert(make_pair(make_pair(901,1000),174));
    mini_cache1.insert(make_pair(make_pair(1001,1100),169));
    mini_cache1.insert(make_pair(make_pair(1101,1200),182));
    mini_cache1.insert(make_pair(make_pair(1201,1300),177));
    mini_cache1.insert(make_pair(make_pair(1301,1400),177));
    mini_cache1.insert(make_pair(make_pair(1401,1500),172));
    mini_cache1.insert(make_pair(make_pair(1501,1600),167));
    mini_cache1.insert(make_pair(make_pair(1601,1700),180));
    mini_cache1.insert(make_pair(make_pair(1701,1800),180));
    mini_cache1.insert(make_pair(make_pair(1801,1900),175));
    mini_cache1.insert(make_pair(make_pair(1901,2000),175));
    mini_cache1.insert(make_pair(make_pair(2001,2100),157));
    mini_cache1.insert(make_pair(make_pair(2101,2200),170));
    mini_cache1.insert(make_pair(make_pair(2201,2300),183));
    mini_cache1.insert(make_pair(make_pair(2301,2400),183));
    mini_cache1.insert(make_pair(make_pair(2401,2500),209));
    mini_cache1.insert(make_pair(make_pair(2501,2600),178));
    mini_cache1.insert(make_pair(make_pair(2601,2700),191));
    mini_cache1.insert(make_pair(make_pair(2701,2800),173));
    mini_cache1.insert(make_pair(make_pair(2801,2900),173));
    mini_cache1.insert(make_pair(make_pair(2901,3000),217));
    mini_cache1.insert(make_pair(make_pair(3001,3100),186));
    mini_cache1.insert(make_pair(make_pair(3101,3200),199));
    mini_cache1.insert(make_pair(make_pair(3201,3300),168));
    mini_cache1.insert(make_pair(make_pair(3301,3400),181));
    mini_cache1.insert(make_pair(make_pair(3401,3500),181));
    mini_cache1.insert(make_pair(make_pair(3501,3600),194));
    mini_cache1.insert(make_pair(make_pair(3601,3700),207));
    mini_cache1.insert(make_pair(make_pair(3701,3800),238));
    mini_cache1.insert(make_pair(make_pair(3801,3900),176));
    mini_cache1.insert(make_pair(make_pair(3901,4000),189));
    mini_cache1.insert(make_pair(make_pair(4001,4100),189));
    mini_cache1.insert(make_pair(make_pair(4101,4200),189));
    mini_cache1.insert(make_pair(make_pair(4201,4300),202));
    mini_cache1.insert(make_pair(make_pair(4301,4400),215));
    mini_cache1.insert(make_pair(make_pair(4401,4500),184));
    mini_cache1.insert(make_pair(make_pair(4501,4600),184));
    mini_cache1.insert(make_pair(make_pair(4601,4700),184));
    mini_cache1.insert(make_pair(make_pair(4701,4800),197));
    mini_cache1.insert(make_pair(make_pair(4801,4900),179));
    mini_cache1.insert(make_pair(make_pair(4901,5000),210));
    mini_cache1.insert(make_pair(make_pair(5001,5100),179));
    mini_cache1.insert(make_pair(make_pair(5101,5200),179));
    mini_cache1.insert(make_pair(make_pair(5201,5300),192));
    mini_cache1.insert(make_pair(make_pair(5301,5400),192));
    mini_cache1.insert(make_pair(make_pair(5401,5500),192));
    mini_cache1.insert(make_pair(make_pair(5501,5600),236));
    mini_cache1.insert(make_pair(make_pair(5601,5700),205));
    mini_cache1.insert(make_pair(make_pair(5701,5800),205));
    mini_cache1.insert(make_pair(make_pair(5801,5900),218));
    mini_cache1.insert(make_pair(make_pair(5901,6000),187));
    mini_cache1.insert(make_pair(make_pair(6001,6100),187));
    mini_cache1.insert(make_pair(make_pair(6101,6200),262));
    mini_cache1.insert(make_pair(make_pair(6201,6300),187));
    mini_cache1.insert(make_pair(make_pair(6301,6400),200));
    mini_cache1.insert(make_pair(make_pair(6401,6500),169));
    mini_cache1.insert(make_pair(make_pair(6501,6600),244));
    mini_cache1.insert(make_pair(make_pair(6601,6700),182));
    mini_cache1.insert(make_pair(make_pair(6701,6800),182));
    mini_cache1.insert(make_pair(make_pair(6801,6900),182));
    mini_cache1.insert(make_pair(make_pair(6901,7000),257));
    mini_cache1.insert(make_pair(make_pair(7001,7100),195));
    mini_cache1.insert(make_pair(make_pair(7101,7200),195));
    mini_cache1.insert(make_pair(make_pair(7201,7300),177));
    mini_cache1.insert(make_pair(make_pair(7301,7400),208));
    mini_cache1.insert(make_pair(make_pair(7401,7500),239));
    mini_cache1.insert(make_pair(make_pair(7501,7600),208));
    mini_cache1.insert(make_pair(make_pair(7601,7700),177));
    mini_cache1.insert(make_pair(make_pair(7701,7800),221));
    mini_cache1.insert(make_pair(make_pair(7801,7900),190));
    mini_cache1.insert(make_pair(make_pair(7901,8000),252));
    mini_cache1.insert(make_pair(make_pair(8001,8100),190));
    mini_cache1.insert(make_pair(make_pair(8101,8200),190));
    mini_cache1.insert(make_pair(make_pair(8201,8300),190));
    mini_cache1.insert(make_pair(make_pair(8301,8400),234));
    mini_cache1.insert(make_pair(make_pair(8401,8500),203));
    mini_cache1.insert(make_pair(make_pair(8501,8600),203));
    mini_cache1.insert(make_pair(make_pair(8601,8700),203));
    mini_cache1.insert(make_pair(make_pair(8701,8800),216));
    mini_cache1.insert(make_pair(make_pair(8801,8900),185));
    mini_cache1.insert(make_pair(make_pair(8901,9000),247));
    mini_cache1.insert(make_pair(make_pair(9001,9100),185));
    mini_cache1.insert(make_pair(make_pair(9101,9200),198));
    mini_cache1.insert(make_pair(make_pair(9201,9300),260));
    mini_cache1.insert(make_pair(make_pair(9301,9400),198));
    mini_cache1.insert(make_pair(make_pair(9401,9500),198));
    mini_cache1.insert(make_pair(make_pair(9501,9600),198));
    mini_cache1.insert(make_pair(make_pair(9601,9700),185));
    mini_cache1.insert(make_pair(make_pair(9701,9800),198));
    mini_cache1.insert(make_pair(make_pair(9801,9900),242));

    mini_cache2.insert(make_pair(make_pair(1,500),144));
    mini_cache2.insert(make_pair(make_pair(501,1000),179));
    mini_cache2.insert(make_pair(make_pair(1001,1500),182));
    mini_cache2.insert(make_pair(make_pair(1501,2000),180));
    mini_cache2.insert(make_pair(make_pair(2001,2500),209));
    mini_cache2.insert(make_pair(make_pair(2501,3000),217));
    mini_cache2.insert(make_pair(make_pair(3001,3500),199));
    mini_cache2.insert(make_pair(make_pair(3501,4000),238));
    mini_cache2.insert(make_pair(make_pair(4001,4500),215));
    mini_cache2.insert(make_pair(make_pair(4501,5000),210));
    mini_cache2.insert(make_pair(make_pair(5001,5500),192));
    mini_cache2.insert(make_pair(make_pair(5501,6000),236));
    mini_cache2.insert(make_pair(make_pair(6001,6500),262));
    mini_cache2.insert(make_pair(make_pair(6501,7000),257));
    mini_cache2.insert(make_pair(make_pair(7001,7500),239));
    mini_cache2.insert(make_pair(make_pair(7501,8000),252));
    mini_cache2.insert(make_pair(make_pair(8001,8500),234));
    mini_cache2.insert(make_pair(make_pair(8501,9000),247));
    mini_cache2.insert(make_pair(make_pair(9001,9500),260));
    mini_cache2.insert(make_pair(make_pair(9501,10000),242));
    mini_cache2.insert(make_pair(make_pair(10001,10500),255));
    mini_cache2.insert(make_pair(make_pair(10501,11000),268));
    mini_cache2.insert(make_pair(make_pair(11001,11500),237));
    mini_cache2.insert(make_pair(make_pair(11501,12000),250));
    mini_cache2.insert(make_pair(make_pair(12001,12500),263));
    mini_cache2.insert(make_pair(make_pair(12501,13000),263));
    mini_cache2.insert(make_pair(make_pair(13001,13500),276));
    mini_cache2.insert(make_pair(make_pair(13501,14000),258));
    mini_cache2.insert(make_pair(make_pair(14001,14500),209));
    mini_cache2.insert(make_pair(make_pair(14501,15000),271));
    mini_cache2.insert(make_pair(make_pair(15001,15500),271));
    mini_cache2.insert(make_pair(make_pair(15501,16000),253));
    mini_cache2.insert(make_pair(make_pair(16001,16500),266));
    mini_cache2.insert(make_pair(make_pair(16501,17000),266));
    mini_cache2.insert(make_pair(make_pair(17001,17500),235));
    mini_cache2.insert(make_pair(make_pair(17501,18000),279));
    mini_cache2.insert(make_pair(make_pair(18001,18500),248));
    mini_cache2.insert(make_pair(make_pair(18501,19000),261));
    mini_cache2.insert(make_pair(make_pair(19001,19500),212));
    mini_cache2.insert(make_pair(make_pair(19501,20000),274));
    mini_cache2.insert(make_pair(make_pair(20001,20500),243));
    mini_cache2.insert(make_pair(make_pair(20501,21000),256));
    mini_cache2.insert(make_pair(make_pair(21001,21500),256));
    mini_cache2.insert(make_pair(make_pair(21501,22000),269));
    mini_cache2.insert(make_pair(make_pair(22001,22500),269));
    mini_cache2.insert(make_pair(make_pair(22501,23000),269));
    mini_cache2.insert(make_pair(make_pair(23001,23500),251));
    mini_cache2.insert(make_pair(make_pair(23501,24000),282));
    mini_cache2.insert(make_pair(make_pair(24001,24500),251));
    mini_cache2.insert(make_pair(make_pair(24501,25000),264));
    mini_cache2.insert(make_pair(make_pair(25001,25500),264));
    mini_cache2.insert(make_pair(make_pair(25501,26000),233));
    mini_cache2.insert(make_pair(make_pair(26001,26500),277));
    mini_cache2.insert(make_pair(make_pair(26501,27000),308));
    mini_cache2.insert(make_pair(make_pair(27001,27500),259));
    mini_cache2.insert(make_pair(make_pair(27501,28000),259));
    mini_cache2.insert(make_pair(make_pair(28001,28500),259));
    mini_cache2.insert(make_pair(make_pair(28501,29000),228));
    mini_cache2.insert(make_pair(make_pair(29001,29500),272));
    mini_cache2.insert(make_pair(make_pair(29501,30000),272));
    mini_cache2.insert(make_pair(make_pair(30001,30500),272));
    mini_cache2.insert(make_pair(make_pair(30501,31000),254));
    mini_cache2.insert(make_pair(make_pair(31001,31500),285));
    mini_cache2.insert(make_pair(make_pair(31501,32000),285));
    mini_cache2.insert(make_pair(make_pair(32001,32500),267));
    mini_cache2.insert(make_pair(make_pair(32501,33000),267));
    mini_cache2.insert(make_pair(make_pair(33001,33500),267));
    mini_cache2.insert(make_pair(make_pair(33501,34000),267));
    mini_cache2.insert(make_pair(make_pair(34001,34500),311));
    mini_cache2.insert(make_pair(make_pair(34501,35000),280));
    mini_cache2.insert(make_pair(make_pair(35001,35500),311));
    mini_cache2.insert(make_pair(make_pair(35501,36000),324));
    mini_cache2.insert(make_pair(make_pair(36001,36500),249));
    mini_cache2.insert(make_pair(make_pair(36501,37000),231));
    mini_cache2.insert(make_pair(make_pair(37001,37500),262));
    mini_cache2.insert(make_pair(make_pair(37501,38000),306));
    mini_cache2.insert(make_pair(make_pair(38001,38500),244));
    mini_cache2.insert(make_pair(make_pair(38501,39000),244));
    mini_cache2.insert(make_pair(make_pair(39001,39500),275));
    mini_cache2.insert(make_pair(make_pair(39501,40000),306));
    mini_cache2.insert(make_pair(make_pair(40001,40500),275));
    mini_cache2.insert(make_pair(make_pair(40501,41000),288));
    mini_cache2.insert(make_pair(make_pair(41001,41500),244));
    mini_cache2.insert(make_pair(make_pair(41501,42000),257));
    mini_cache2.insert(make_pair(make_pair(42001,42500),288));
    mini_cache2.insert(make_pair(make_pair(42501,43000),257));
    mini_cache2.insert(make_pair(make_pair(43001,43500),257));
    mini_cache2.insert(make_pair(make_pair(43501,44000),270));
    mini_cache2.insert(make_pair(make_pair(44001,44500),270));
    mini_cache2.insert(make_pair(make_pair(44501,45000),270));
    mini_cache2.insert(make_pair(make_pair(45001,45500),314));
    mini_cache2.insert(make_pair(make_pair(45501,46000),239));
    mini_cache2.insert(make_pair(make_pair(46001,46500),283));
    mini_cache2.insert(make_pair(make_pair(46501,47000),252));
    mini_cache2.insert(make_pair(make_pair(47001,47500),314));
    mini_cache2.insert(make_pair(make_pair(47501,48000),283));
    mini_cache2.insert(make_pair(make_pair(48001,48500),252));
    mini_cache2.insert(make_pair(make_pair(48501,49000),296));
    mini_cache2.insert(make_pair(make_pair(49001,49500),265));    
}


// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
	using namespace std;

	assert(i > 0);
	assert(j > 0);


    int min_val = min(i,j);
    int max_val = max(i,j);

    map<pair<int,int>,int>::iterator iter1 = mini_cache1.begin();
    map<pair<int,int>,int>::iterator iter2 = mini_cache2.begin();

	int _max = 1;
	int steps = 1;
	int second_val=0;

    /* One of the most common tests, we'll just return 525 the expected value */
    if(min_val == 1 && max_val == 999999) return 525;

    int m = max_val / 2 + 1;
    if (m > min_val){
    	min_val = m;
    }
    unsigned cur  = min_val;

    for(i=min_val;i<=max_val;i++, cur=i, steps= 1 ){

        /*
         *For the cache we just increase i and everytime we hit
         * a number divisible by 100 or 500 we check whether it's already cached.
         * If it is we use the cached value and increment i by 99 or 499
         * to jump to the end of the range.
        */

        if(i % 500==1 &&  i+499 <= max_val  &&i <= 49001){

        iter2 =  mini_cache2.find(std::pair<int,int> (i,i+499));

        /*
            Just check whether number is actually cached
        */
        if(iter2!=mini_cache2.end()){
            second_val = iter2->second;
            i +=499;
            if(_max < second_val){
                // Assign new value
                _max = second_val;
             }
            continue;
        }
        
        }else if(i % 100 ==1 && i+99 <= max_val && i <= 9801){

        iter1 =  mini_cache1.find(std::pair<int,int> (i,i+99));

        /*
            Just check whether number is actually cached
        */
        if(iter1!=mini_cache1.end()){
                second_val = iter1->second;
                i+=99;    

            if(_max < second_val){ 
                //Assign new value
                _max = second_val;
            }
            continue;
        }    
       }
        int solving = cur ;
       // Template 3n+1 algorithm with a few efficiencies.
        while(cur!=1){
//        	cout << "max: " << max_val<< " solving for: " << solving << " at: " << cur << endl;
            if(cur % 2 == 0){
                cur=cur>>1;
            }else{
                cur=cur+ (cur>>1) + 1;
                ++steps;
            }
            ++steps;
        }

        if(steps > _max) _max = steps;
    }

    return _max;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
        collatz_cache();
        string s;
        while (getline(r, s)) {
            const pair<int, int> p = collatz_read(s);
            const int            i = p.first;
            const int            j = p.second;
            const int            v = collatz_eval(i, j);
            collatz_print(w, i, j, v);}
        }

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}
