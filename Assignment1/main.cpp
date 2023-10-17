#include <iostream>
#include <vector>
using namespace std;

    class SET{
        private:
        int num;
        vector<int> contents = {};

        public:
        vector<int>::iterator i;
        int insert(int n){
            int l = 0;
            int r = contents.size() - 1;
            int centre;
            while (l<=r){
                centre = l + (r-l)/2;
                if (contents.at(centre)==n){
                    return contents.size();
                }
                else if (contents.at(centre)>n){
                    if (centre==0){
                        contents.insert(contents.begin(),n);
                        return contents.size();
                    }
                    else if (contents.at(centre-1)<n){
                        contents.insert(contents.begin()+centre,n);
                        return contents.size();
                    }
                    r = centre - 1;
                }
                else{
                    if (centre==contents.size()-1){
                        contents.insert(contents.end(),n);
                        return contents.size();
                    }
                    else if (contents.at(centre+1)>n){
                        contents.insert(contents.begin()+centre+1,n);
                        return contents.size();
                    }
                    l = centre + 1;
                }
        }
        contents.insert(contents.begin(),n);
        return contents.size();
        }

        int unionset(SET s){
            for(i = s.contents.begin(); i!=s.contents.end(); i+=1){
                this->insert(*i);
            }
            return contents.size();
        }

        int intersection(SET s){
            vector<int> s1 = contents;
            contents.clear();
            for(i = s1.begin(); i!=s1.end(); i+=1){
                if (s.belongsto(*i)==1){
                    contents.push_back(*i);
                }
            }
            return contents.size();
        }

        int difference(SET s){
            for(i = s.contents.begin(); i!=s.contents.end(); i+=1){
                if (this->belongsto(*i)==1){
                    this->deletion(*i);
                }
            }
            return contents.size();
        }

        int symdifference(SET s){
            for(i = s.contents.begin(); i!=s.contents.end(); i+=1){
                if (this->belongsto(*i)==0){
                    this->insert(*i);
                }
                else{
                    this->deletion(*i);
                }
                
            }
            return contents.size();
        }

        int deletion(int o){
            int l = 0;
            int r = contents.size() - 1;
            int centre;
            while (l<=r){
                centre = l + (r-l)/2;
                if (contents.at(centre)==o){
                    contents.erase(contents.begin() + centre);
                    return contents.size();
                }
                else if (contents.at(centre)>o){
                    r = centre - 1;
                }
                else{
                    l = centre + 1;
                }
            

            }
            return contents.size();
        }

        int size(){
            return contents.size();
        }

        void print(){
            for(i = contents.begin(); i!=contents.end(); i+=1){
                if (i==contents.end()-1){
                    cout<<*i<<endl;
                }
                else{
                    cout<<*i<<",";
                }
            }
            
            if (contents.size()==0){
            cout<<endl;
            }
        }

        int belongsto(int m){
            int l = 0;
            int r = contents.size() - 1;
            int centre;
            while (l<=r){
                centre = l + (r-l)/2;
                if (contents.at(centre)==m){
                    return 1;
                }
                else if (contents.at(centre)>m){
                    r = centre - 1;
                }
                else{
                    l = centre + 1;
                }
            }
            return 0;
        }
    };

    void out(int a, int b, int c, int &setnum, vector<SET> &helo){
    switch (a){
        case 1:
        if (setnum<b){
            SET *p = new SET;
            helo.push_back(*p);
            cout<<helo[b].insert(c)<<endl;
            setnum+=1;
            delete p;
        }
        else{
            cout<<helo[b].insert(c)<<endl;
        }
        break;

        case 2:
        if (setnum<b){
            cout<<-1<<endl;
        }
        else{
            cout<<helo[b].deletion(c)<<endl;
        }
        break;

        case 3:
        if (setnum<b){
            cout<<-1<<endl;
        }
        else{
            cout<<helo[b].belongsto(c)<<endl;
        }
        break;

        case 4:
        if (setnum<b){
        	SET *p = new SET;
            helo.push_back(*p);
            setnum+=1;
            delete p;
        }
        if (setnum<c){
        	SET *p = new SET;
            helo.push_back(*p);
            setnum+=1;
            delete p;
        }
        cout<<helo[b].unionset(helo[c])<<endl;
        break;

        case 5:
        if (setnum<b){
		SET *p = new SET;
            helo.push_back(*p);
            setnum+=1;
            delete p;
        }
        if (setnum<c){
		SET *p = new SET;
            helo.push_back(*p);
            setnum+=1;
            delete p;
        }
        cout<<helo[b].intersection(helo[c])<<endl;
        break;

        case 6:
        if (setnum<b){
            SET *p = new SET;
            helo.push_back(*p);
            setnum+=1;
                        delete p;
        }
        cout<<helo[b].size()<<endl;
        break;

        case 7:
        if (setnum<b){
            SET *p = new SET;
            helo.push_back(*p);
            setnum+=1;
                        delete p;
        }
        if (setnum<c){
            SET *p = new SET;
            helo.push_back(*p);
            setnum+=1;
                        delete p;
        }
        cout<<helo[b].difference(helo[c])<<endl;
        break;

        case 8:
        if (setnum<b){
            SET *p = new SET;
            helo.push_back(*p);
            setnum+=1;
                        delete p;
        }
        if (setnum<c){
            SET *p = new SET;
            helo.push_back(*p);
            setnum+=1;
                        delete p;
        }
        cout<<helo[b].symdifference(helo[c])<<endl;
        break;

        case 9:
        if (setnum<b){
            cout<<endl;
        }
        else{
            helo[b].print();
        }
        break;
    }
    }

int main() {
    vector<SET> helo;
    int a, b, c;
    int numset = -1;
    while (cin>>a){
        if (a==6 or a==9){
            cin>>b;
            out(a,b,c,numset,helo);
        }
        else{
            cin>>b>>c;
            out(a,b,c,numset,helo);
        }
    }
  return 0;
}