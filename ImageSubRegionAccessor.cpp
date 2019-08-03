#include <iostream>
#include <vector>
#include <string>

class Image
{
	const uint32_t Lc;
	const uint32_t Ac;
	const uint32_t Fc;

public:
	Image(uint32_t lc, uint32_t ac, uint32_t fc) : Lc(lc), Ac(ac), Fc(fc) {};

	uint32_t GetOffset(const uint32_t& L)
	{
		auto La = L * Ac * Fc;
		auto Lb = Ac * L + L;
		auto LO = La + Lb;

		return LO;
	};
	uint32_t GetOffset(const uint32_t& L, const uint32_t& A)
	{
		auto La = L * Ac * Fc;
		auto Lb = Ac * L + L;
		auto LO = La + Lb;

		auto AO = Fc * A + A + 1;

		return LO + AO;
	};
	uint32_t GetOffset(const uint32_t& L, const uint32_t& A, const uint32_t& F)
	{
		auto La = L * Ac * Fc;
		auto Lb = Ac * L + L;
		auto LO = La + Lb;

		auto AO = (Fc * A) + A;

		return LO + AO + F + 2;
	};
};

int main()
{
	Image img(5, 1, 6);
	Image img2(3, 3, 6);

	std::cout << "Offset of L0         = " << img.GetOffset(0) << "  expected: 0" << std::endl;
	std::cout << "Offset of L1         = " << img.GetOffset(1) << "  expected: 8" << std::endl;
	std::cout << "Offset of L2         = " << img.GetOffset(2) << " expected: 16" << std::endl;
	std::cout << "Offset of L3         = " << img.GetOffset(3) << " expected: 24" << std::endl;
	std::cout << "Offset of L4         = " << img.GetOffset(4) << " expected: 32" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "Offset of L0, A0     = " << img2.GetOffset(0, 0) << "  expected: 1" << std::endl;
	std::cout << "Offset of L0, A1     = " << img2.GetOffset(0, 1) << "  expected: 8" << std::endl;
	std::cout << "Offset of L0, A2     = " << img2.GetOffset(0, 2) << " expected: 15" << std::endl;
	std::cout << "Offset of L1, A0     = " << img2.GetOffset(1, 0) << " expected: 23" << std::endl;
	std::cout << "Offset of L1, A1     = " << img2.GetOffset(1, 1) << " expected: 30" << std::endl;
	std::cout << "Offset of L1, A2     = " << img2.GetOffset(1, 2) << " expected: 37" << std::endl;
	std::cout << "Offset of L2, A0     = " << img2.GetOffset(2, 0) << " expected: 45" << std::endl;
	std::cout << "Offset of L2, A1     = " << img2.GetOffset(2, 1) << " expected: 52" << std::endl;
	std::cout << "Offset of L2, A2     = " << img2.GetOffset(2, 2) << " expected: 59" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "Offset of L0, A0, F0 = " << img2.GetOffset(0, 0, 0) << "  expected: 2" << std::endl;
	std::cout << "Offset of L0, A0, F1 = " << img2.GetOffset(0, 0, 1) << "  expected: 3" << std::endl;
	std::cout << "Offset of L0, A0, F2 = " << img2.GetOffset(0, 0, 2) << "  expected: 4" << std::endl;
	std::cout << "Offset of L0, A1, F3 = " << img2.GetOffset(0, 1, 3) << " expected: 12" << std::endl;
	std::cout << "Offset of L0, A1, F4 = " << img2.GetOffset(0, 1, 4) << " expected: 13" << std::endl;
	std::cout << "Offset of L0, A2, F5 = " << img2.GetOffset(0, 2, 5) << " expected: 21" << std::endl;
	std::cout << "Offset of L1, A0, F4 = " << img2.GetOffset(1, 0, 4) << " expected: 28" << std::endl;
	std::cout << "Offset of L1, A0, F5 = " << img2.GetOffset(1, 0, 5) << " expected: 29" << std::endl;
	std::cout << "Offset of L1, A1, F3 = " << img2.GetOffset(1, 1, 3) << " expected: 34" << std::endl;
	std::cout << "Offset of L1, A1, F4 = " << img2.GetOffset(1, 1, 4) << " expected: 35" << std::endl;
	std::cout << "Offset of L2, A1, F2 = " << img2.GetOffset(2, 1, 2) << " expected: 55" << std::endl;
	std::cout << "Offset of L2, A1, F3 = " << img2.GetOffset(2, 1, 3) << " expected: 56" << std::endl;

	return 0;
}
