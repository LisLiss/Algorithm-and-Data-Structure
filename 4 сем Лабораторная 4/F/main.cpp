#include <bits/stdc++.h>


using namespace std;

static constexpr double PI = std::atan(1.0) * 4;

typedef complex<double> base;


vector <base> fourier (vector<base> a, bool f) {
	if (a.size()==1) return a;
	vector<base> help0(a.size()/2);
	vector<base> help1(a.size()/2);
	int j=0;
	for (int i=0; i<a.size(); i+=2) {
		help0[j] = a[i];
		help1[j] = a[i+1];
		j++;
	}
	help0=fourier(help0,f);
	help1=fourier(help1,f);
	double u=2*PI/a.size();
	if (f) u*=-1;
	base first(1),  second(cos(u), sin(u));
	for (int i=0; i<a.size()/2; i++) {
		a[i] = help0[i]+first*help1[i];
		a[i+a.size()/2] = help0[i]-first*help1[i];
		if (f){
            a[i]/=2;
            a[i+a.size()/2]/=2;
		}
		first*=second;
	}
	return a;
}

int main(){
    vector <int> a, b, ans;
    string sa, sb;
    cin>>sa>>sb;
    bool fa, fb;
    fa=sa[0]=='-';
    fb=sb[0]=='-';
    for (int i=sa.size()-1; i>0; i--){
        a.push_back(sa[i]-'0');
    }
    if (!fa) a.push_back(sa[0]-'0');
    for (int i=sb.size()-1; i>0; i--){
        b.push_back(sb[i]-'0');
    }
    if (!fb) b.push_back(sb[0]-'0');
    vector<base> ca (a.begin(), a.end()),  cb (b.begin(), b.end());
	int n=1;
	while (n<max(a.size(), b.size())){
        n=n<<1;
	}
	n=n<<1;
	ans.resize (n);
	ca.resize(n);
    ca=fourier(ca, false);
	cb.resize(n);
	cb=fourier(cb, false);
	for (int i=0; i<n; i++){
		ca[i]*=cb[i];
	}
	ca=fourier(ca, true);
	for (int i=0; i<n; i++){
		ans[i]=int(ca[i].real()+0.5);
	}
	int help=0;
	for (size_t i=0; i<n; ++i) {
		ans[i]+=help;
		help=ans[i]/10;
		ans[i]%=10;
	}
	if (help!=0) ans.push_back(help);
	int flag=ans.size()-1;
	for (int i=ans.size()-1; i>-1; i--){
        if (ans[i]==0){
            flag=i;
        } else{
            break;
        }
	}
	if (flag==0){
        cout<<"0";
        return 0;
	}
	if (fa && !fb || !fa && fb) cout<<"-";
	for (int i=flag-1; i>-1; i--){
        cout<<ans[i];
	}
    return 0;
}
