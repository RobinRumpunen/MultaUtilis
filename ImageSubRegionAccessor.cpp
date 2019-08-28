#include <iostream>

class Image
{
	const uint32_t Lc;
	const uint32_t Ec;
	const uint32_t Fc;

public:
	Image(uint32_t lc, uint32_t ec, uint32_t fc) : Lc(lc), Ec(ec), Fc(fc) {};

	// @brief return the offset into an array of linearly arranged elements in the hierarchy Level/Element/Face.
	// @param - allowed range is [1-N], where 1 is the first element of the subregion.
	inline uint32_t GetOffset(const uint32_t& L = 1, const uint32_t& E = 0, const uint32_t& F = 0)
	{
		/// Ensure we only operate on whole numbers.
		//auto L0 = L <= 1 ? 0 : L - 1;
		//auto E0 = E <= 1 ? 0 : E - 1;
		///	 Level offset			 Element offset	     Face offset
		//return (L0 * ((Ac * Fc) + Ac + 1))  +  ((E0 * Fc) + E)  +  F;

		return ((L <= 1 ? 0 : L - 1) * ((Ec * Fc) + Ec + 1)) + ((E <= 1 ? 0 : E - 1) * Fc) + E + F;
	};
};

int main()
{
	Image img(5, 1, 6);
	Image img2(3, 3, 6);

	std::cout << "Offset of L1         = " << img.GetOffset(1) << "  expected: 0" << std::endl;
	std::cout << "Offset of L2         = " << img.GetOffset(2) << "  expected: 8" << std::endl;
	std::cout << "Offset of L3         = " << img.GetOffset(3) << " expected: 16" << std::endl;
	std::cout << "Offset of L4         = " << img.GetOffset(4) << " expected: 24" << std::endl;
	std::cout << "Offset of L5         = " << img.GetOffset(5) << " expected: 32" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "Offset of L0, A0     = " << img2.GetOffset(1, 1) << "  expected: 1" << std::endl;
	std::cout << "Offset of L0, A1     = " << img2.GetOffset(1, 2) << "  expected: 8" << std::endl;
	std::cout << "Offset of L0, A2     = " << img2.GetOffset(1, 3) << " expected: 15" << std::endl;
	std::cout << "Offset of L1, A0     = " << img2.GetOffset(2, 1) << " expected: 23" << std::endl;
	std::cout << "Offset of L1, A1     = " << img2.GetOffset(2, 2) << " expected: 30" << std::endl;
	std::cout << "Offset of L1, A2     = " << img2.GetOffset(2, 3) << " expected: 37" << std::endl;
	std::cout << "Offset of L2, A0     = " << img2.GetOffset(3, 1) << " expected: 45" << std::endl;
	std::cout << "Offset of L2, A1     = " << img2.GetOffset(3, 2) << " expected: 52" << std::endl;
	std::cout << "Offset of L2, A2     = " << img2.GetOffset(3, 3) << " expected: 59" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "Offset of L0, A0, F0 = " << img2.GetOffset(1, 1, 1) << "  expected: 2" << std::endl;
	std::cout << "Offset of L0, A0, F1 = " << img2.GetOffset(1, 1, 2) << "  expected: 3" << std::endl;
	std::cout << "Offset of L0, A0, F2 = " << img2.GetOffset(1, 1, 3) << "  expected: 4" << std::endl;
	std::cout << "Offset of L0, A1, F3 = " << img2.GetOffset(1, 2, 4) << " expected: 12" << std::endl;
	std::cout << "Offset of L0, A1, F4 = " << img2.GetOffset(1, 2, 5) << " expected: 13" << std::endl;
	std::cout << "Offset of L0, A2, F5 = " << img2.GetOffset(1, 3, 6) << " expected: 21" << std::endl;
	std::cout << "Offset of L1, A0, F4 = " << img2.GetOffset(2, 1, 5) << " expected: 28" << std::endl;
	std::cout << "Offset of L1, A0, F5 = " << img2.GetOffset(2, 1, 6) << " expected: 29" << std::endl;
	std::cout << "Offset of L1, A1, F3 = " << img2.GetOffset(2, 2, 4) << " expected: 34" << std::endl;
	std::cout << "Offset of L1, A1, F4 = " << img2.GetOffset(2, 2, 5) << " expected: 35" << std::endl;
	std::cout << "Offset of L2, A1, F2 = " << img2.GetOffset(3, 2, 3) << " expected: 55" << std::endl;
	std::cout << "Offset of L2, A1, F3 = " << img2.GetOffset(3, 2, 4) << " expected: 56" << std::endl;

	return 0;
}
