int distance(SDL_Point a, SDL_Point b) {
	return ceil(sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2)));
}
bool Collide(SDL_Rect* S1, SDL_Rect* S2) {
	return SDL_HasIntersection(S1, S2);
}
void int2str(int a, char str[]) {
	int len=0;
	char ch;
	if(a==0) {
		str[0]='0';
		len++;
	}
	for(; a>0; a/=10, len++) {
		str[len]=(a%10)+'0';
	}
	for(int j=0; j<len/2; j++){
		ch=str[j];
		str[j]=str[len-j-1];
		str[len-j-1]=ch;
	}
	str[len]='\0';
}