struct node
{
    ll n,d;
    bool operator<(const node&x)const
    {
        return d>x.d;//��Ϊpriority queue�Ǵ�������Է���Ҫ������
    }
};
