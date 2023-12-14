#include <iostream>
using namespace std;

class Porter_Stemmer{
	private:
        string word;
	    int idx, end;
        
        bool ends_with(string suf){
            if (word.length() - suf.length() < 0){
                return false;
            }
            for (int i = 0; i < suf.length(); i++){
                if (suf[i]!=word[word.length()-suf.length()+i]){
                    return false;
                }
            }
            return true;
        }

        bool IsConsonant (int idx){
            string vow = "aeiou";
            for (int i = 0; i < 5; i++){
                if (vow[i]==word[idx]){
                    return false;
                }
            }
            if (word[idx]!='y'){
                return true;
            }

            if (idx==0){
                return true;
            }
            else{
                return IsConsonant(idx - 1);
            }
        }

        int VCcount (int n = 0){
            int m = 0, idx = 0;
            while (idx<=end - n and IsConsonant(idx)){
                idx++;
            }
            if (idx > end - n){
                return false;
            }

            idx++;
            while (1){
                while (idx <= end - n and !IsConsonant(idx)){
                    idx++;
                }

                idx++;
                m++;

                while (idx <= end - n and IsConsonant(idx)){
                    idx++;
                }

                if (idx > end - n){
                    return m;
                }
            }
        }

        bool ContainsVowels(int n = 0){
            for (int i = 0; i <= end - n; i++){
                if (!IsConsonant(i)){
                    return true;
                }
            }
            return false;
        }

        bool CVC_end (int idx){
            if (idx < 2 or !IsConsonant(idx) or IsConsonant(idx - 1) or !IsConsonant(idx - 2)){
                return false;
            }
            else{
                string s = "wxy";
                bool c = true;
                for (int i = 0; i < 3; i++){
                    if (s[i]==word[end]){
                        c = false;
                    }
                }
                return c;
            }
        }

	// Get the stem of a word at least three letters long:
	public:
        string stemmed_word (string OGword){
            if (OGword.length()<3){
                return OGword;
            }

            word = OGword;
            idx = 0;
            end = word.length() - 1;

            remove_plurals();
            remove_double_suffixes();
            simple_ends();
            simple_ends2();
            tidy_up();
            return word;
        }
        
        // Step 1: remove plurals and past participles:
        void remove_plurals (){
            if (ends_with("s"))          //Step 1a
            {
                if (ends_with("sses")){
                    word.pop_back();
                    word.pop_back();
                    end-=2;
                }
                else if (ends_with("ies")){ 
                    word.pop_back();
                    word.pop_back();
                    end-=2;
                }
                else if (ends_with("ss")){ 
                }
                else if (ends_with("s")){ 
                    word.pop_back();
                    end-=1;
                }
            }

            if (ends_with("eed")){        //Step 1b
                if (VCcount(3) > 0){
                    word.pop_back();
                    end-=1;
                }
            }
            else if (ends_with("ed") and ContainsVowels(2)){
                word.pop_back();
                word.pop_back();
                end-=2;
                if (ends_with("at") or ends_with("bl") or ends_with("iz")){
                    word+='e';
                    end+=1;
                }
                else if (end > 0 and word[end]==word[end-1] and IsConsonant(end)){
                    string s = "lsz";
                    bool c = false;
                    for (int i = 0; i < 3; i++){
                        if (s[i]==word[end]){
                            c = true;
                        }
                    }
                    if (c==false){
                        word.pop_back();
                        end-=1;
                    }
                }
                else if (VCcount(2) == 1 and CVC_end(end)){
                    word+='e';
                    end+=1;
                }
            }
            else if (ends_with("ing") and ContainsVowels(3)){
                word.pop_back();
                word.pop_back();
                word.pop_back();
                end-=3;
                if (ends_with("at") or ends_with("bl") or ends_with("iz")){
                    word+='e';
                    end+=1;
                }
                else if (end > 0 and word[end]==word[end-1] and IsConsonant(end)){
                    string s = "lsz";
                    bool c = false;
                    for (int i = 0; i < 3; i++){
                        if (s[i]==word[end]){
                            c = true;
                        }
                    }
                    if (c==false){
                        word.pop_back();
                        end-=1;
                    }
                }
                else if (VCcount(3) == 1 and CVC_end(end)){
                    word+='e';
                    end+=1;
                }
            }

            if (ends_with("y") and ContainsVowels(1)){             //Step 1c
                word.pop_back();
                word+="i";
            }
        }

        // Step 2: reduce double suffixes to single suffix
        void remove_double_suffixes (){         
            if ((ends_with("ational") or ends_with("ization")) and VCcount(7) > 0){
                word.pop_back();
                word.pop_back();
                word.pop_back();
                word.pop_back();
                word.pop_back();
                word+="e";
                end-=4;
            }
            else if ((ends_with("enci") or ends_with("anci") or ends_with("abli")) and VCcount(4) > 0){
                word.pop_back();
                word+="e";
            }
            else if (ends_with("izer") and VCcount(4) > 0){
                word.pop_back();
                end-=1;
            }
            else if ((ends_with("tional") and VCcount(6) > 0) or ((ends_with("alli") or ends_with("ulli")) and VCcount(4) > 0) or ((ends_with("entli") or ends_with("ousli")) and VCcount(5) > 0) or ((ends_with("eli") or ends_with("ili")) and VCcount(3) > 0)){
                word.pop_back();
                word.pop_back();
                end-=2;
            }
            else if ((ends_with("ation") or ends_with("iviti")) and VCcount(5) > 0){
                word.pop_back();
                word.pop_back();
                word.pop_back();
                word+='e';
                end-=2;
            }
            else if ((ends_with("ator")) and VCcount(4) > 0){
                word.pop_back();
                word.pop_back();
                word+="e";
                end-=1;
            }
            else if ((ends_with("alism") or ends_with("aliti")) and VCcount(5) > 0){
                word.pop_back();
                word.pop_back();
                word.pop_back();
                end-=3;
            }
            else if ((ends_with("iveness") or ends_with("fulness") or ends_with("ousness")) and VCcount(6) > 0){
                word.pop_back();
                word.pop_back();
                word.pop_back();
                word.pop_back();
                end-=4;
            }
            else if ((ends_with("biliti")) and VCcount(6) > 0){
                word.pop_back();
                word.pop_back();
                word.pop_back();
                word.pop_back();
                word.pop_back();
                word+="le";
                end-=3;
            }
        }

        // Step 3: replace -ic-, -full, -ness, etc. with simpler endings:
        void simple_ends(){
            if (VCcount(5) > 0){
                switch (word[end]){
                    case 'e':
                        if (ends_with("icate")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=3;
                        }
                        else if (ends_with("ative")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=5;
                        }
                        else if (ends_with("alize")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=3;
                        }
                        break;
                        return;
                    case 'i':
                        if (ends_with("iciti")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=3;
                        }
                        break;
                        return;
                }
            }
            switch (word[end]){
                case 'l':
                    if (ends_with("ical") and VCcount(4) > 0){
                        word.pop_back();
                        word.pop_back();
                        end-=2;
                    }
                    else if (ends_with("ful") and VCcount(3) > 0){
                        word.pop_back();
                        word.pop_back();
                        word.pop_back();
                        end-=3;
                    }
                    break;
                    return;
                case 's':
                    if (ends_with("ness") and VCcount(4) > 0){
                        word.pop_back();
                        word.pop_back();
                        word.pop_back();
                        end-=4;
                    }
                    break;
                    return;
            }
        }  
        

        // Step 4: remove -ant, -ence, etc.:
        void simple_ends2(){
            if (VCcount(2) > 1){
                switch (word[end - 1]){
                    case 'a':
                        if (ends_with("al")){
                            word.pop_back();
                            word.pop_back();
                            end-=2;
                        }
                        break;
                        return;
                    case 'e':
                        if (ends_with("er")){
                            word.pop_back();
                            word.pop_back();
                            end-=2;
                        }
                        break;
                        return;
                    case 'i':
                        if (ends_with("ic")){
                            word.pop_back();
                            word.pop_back();
                            end-=2;
                        }
                        break; 
                        return;
                }
            }
            if (VCcount(3) > 1){
                switch (word[end - 1]){
                    case 't':
                        if (ends_with("ate")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=3;
                        }
                        else if(ends_with("iti")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=3;
                        }
                        break;
                        return;
                    case 'u':
                        if (ends_with("ous")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=3;
                        }
                    case 'v':
                        if (ends_with("ive")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=3;
                        }
                    case 'z':
                        if (ends_with("ize")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=3;
                        }
                    case 's':
                        if (ends_with("ism")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=3;
                        }
                        break;
                        return;
                }
            }
            if (VCcount(4) > 0){
                switch (word[end - 1]){
                    case 'c':
                        if (ends_with("ance") or ends_with("ence")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=4;
                        }
                        break;
                        return;
                    case 'l':
                        if (ends_with("able")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=4;
                        }
                        else if (ends_with("ible")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=4;
                        }
                        break;
                        return;
                }
            }   
            switch(word[end - 1]){
                case 'n':
                    if (VCcount(3) > 0){
                        if (ends_with("ant")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=3;
                        }
                        else if (ends_with("ent")){
                            word.pop_back();
                            word.pop_back();
                            word.pop_back();
                            end-=3;
                        }
                    }
                    else if (ends_with("ement") and VCcount(5) > 0){
                        word.pop_back();
                        word.pop_back();
                        word.pop_back();
                        word.pop_back();
                        word.pop_back();
                        end-=5;
                    }
                    else if (ends_with("ment") and VCcount(4) > 0){
                        word.pop_back();
                        word.pop_back();
                        word.pop_back();
                        word.pop_back();
                        end-=4;
                    }
                    break;
                case 'o':
                    if ((ends_with("sion") or ends_with("tion")) and VCcount(4) > 0){
                        word.pop_back();
                        word.pop_back();
                        word.pop_back();
                        word.pop_back();
                        end-=4;
                    }
                    else if(ends_with("ou") and VCcount(2) > 0){
                        word.pop_back();
                        word.pop_back();
                        end-=2;
                    }
                    break;
            }
        }

        // Step 5: tidying up:
        void tidy_up(){
            if (VCcount(1) > 1 and word[end]=='e'){          //Step 5a
                word.pop_back();
                end-=1;
            }
            else if (!CVC_end(end) and VCcount(1)==1 and word[end]=='e'){
                word.pop_back();
                end-=1;
            }
            
            if (VCcount(1) > 1 and word[end] == 'l' and word[end - 1] == 'l'){
                word.pop_back();
                end-=1;
            }
        }
};