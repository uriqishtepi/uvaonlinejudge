#include<stdio.h>
#include<math.h>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<functional>
#include<vector>
#include<bitset>
#include<set>
#include<map>
#include <string.h>
#include <iomanip>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define mtsi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define ss std::set<std::string>
#define mi std::map<int, int>
#define mmi std::multimap<int, int>
#define msi std::map<std::string, int>
#define INF 1<<30;

#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

int main(int argc, char **argv)
{
    out("Starting...\n");
    char notes[][3] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B", "C" };

    msi revmap;
    revmap["C"] = 0;
    revmap["C#"] = 1;
    revmap["D"] = 2;
    revmap["D#"] = 3;
    revmap["E"] = 4;
    revmap["F"] = 5;
    revmap["F#"] = 6;
    revmap["G"] = 7;
    revmap["G#"] = 8;
    revmap["A"] = 9;
    revmap["A#"] = 10;
    revmap["B"] = 11;


    //will make a set of chords the first note can be
    //then for every subsequent note, will compare its list of chords
    //with the possible ones from the previous notes
    //whene possible ones are empty break
    
    std::map<int, si > initial; //note to all notes in that chord
    std::map<int, si > full; //note to all chords that nodes is part
    int blah;
    enum { tone = 2, semi_tone = 1};
    int chord[] = { 0, tone, tone, semi_tone, tone, tone, tone, semi_tone};

    forl(i,0,12) {
        int next = i;

        out("full %s: ",notes[i]);
        forl(j,0,sizeof(chord)/sizeof(int)) {
            next += chord[j];
            full[next%12].insert(i); //chords that i takes part in, to i
            initial[i].insert(next%12);
            out( " %s" , notes[next%12] );
        }
        out("\n");

    }
    

    char * buff = NULL;
    size_t n;

    while(getline(&buff, &n, stdin) > 0 && (strncmp(buff,"END", 3) != 0)) 
    {
        out("Read '%s'\n", buff);

        int h, m, s, speed = -1;
        si possible;
        int count = 0;

        char * cptr = strtok(buff, " ");
        if(cptr == NULL || strcmp(cptr, "END") == 0)
            continue;
        out("note %s\n", cptr);

        int curr = revmap[cptr];
        out("curr %d\n", curr);

        //this is the first note, populate the possible set
        possible = initial[curr];

        out("possible size %d: ", possible.size());
        for(si::iterator it = possible.begin();it!=possible.end();++it) {
            out( " %s" , notes[*it] );
        }
        out("\n");



        while((cptr = strtok(NULL, " ")) != NULL) 
        {
            out("note %s\n", cptr);
            int curr = revmap[cptr];
            out("curr %d\n", curr);

            //compare the next notes chords, with the previous possible
            si::iterator jt = possible.begin();
            while(jt != possible.end() )
            {
                bool found = false;
                mmi::iterator it = full.find(*jt);
                si chords = it->second;
                while(it != full.end() && it->first == *jt) {
                    if(curr == it->second) {
                        found = true;
                        break;
                    }
                    ++it;
                }    
                si::iterator tmp = jt;
                ++jt;

                if(!found) {
                    possible.erase(tmp);
                }

        out("possible size %d: ", possible.size());
        for(si::iterator it = possible.begin();it!=possible.end();++it) {
            out( " %s" , notes[*it] );
        }
        out("\n");

            }
        }

        out("Answer possible size %d: ", possible.size());
        for(si::iterator it = possible.begin();it!=possible.end();++it) {
            std::cout << " " << notes[*it] << " ";
        }
        std::cout << std::endl;
    }


    free(buff);
    return 0;
}

