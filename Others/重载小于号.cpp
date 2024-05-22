struct node
{
    ll n,d;
    bool operator<(const node&x)const
    {
        return d>x.d;//因为priority queue是大根堆所以符号要倒过来
    }
};
