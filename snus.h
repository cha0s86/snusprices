class Snus {
	public:
		std::wstring brand;
		std::wstring label;
		std::wstring price;
		std::wstring strength;

		Snus(std::wstring newbrand, std::wstring newlabel, std::wstring newprice, std::wstring newstrength) {
			brand = newbrand;
			label = newlabel;
			price = newprice;
			strength = newstrength;
		}
};
