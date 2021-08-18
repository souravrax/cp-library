class BITrangeOperations
{
public:

	ll BIT[MAX+7][2];

	void upd(int idx, ll x, bool t) {
		while(idx<=MAX)
		{
			BIT[idx][t]+=x;
			idx+=(idx&-idx);
		}
	}
	
	ll qry(int idx, bool t) {
		ll sum=0;
		while(idx>0)
		{
			sum+=BIT[idx][t];
			idx-=(idx&-idx);
		}
		return sum;
	}
	
	// Returns sum from [0,x]
	ll sum(int x) {
		return (query(x,0)*x)-query(x,1);
	}

	void updateRange(int l, int r, ll val) {
		upd(l,val,0);
		upd(r+1,-val,0);
		upd(l,val*(l-1),1);
		upd(r+1,-val*r,1);
	}

	ll rangeSum(int l, int r) {
		return sum(r)-sum(l-1);
	}
};