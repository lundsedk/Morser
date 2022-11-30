#pragma once

//this could probably be done smarter - make the "add signed integer to bbindex" function first
//then run that from most other functions...
//just store the total, but return with the right modal logic
// %= ByteSize modulus assignment

//storing total
//add signed to
//	
//compares easier

//reading even possible?
	//redo as functions?
	// getBitIndex()

template <uint8_t ByteSize = 8>
struct BBIndex {
	uint8_t ByteSizeVar = ByteSize;
	uint64_t TotalIndex = 0;

	BBIndex(const uint64_t newByteIndex = 0, uint64_t newBitIndex = 0)
		: TotalIndex(newByteIndex * ByteSizeVar + newBitIndex)
	{
	}

	bool operator == (const BBIndex& rhs) const {
		return (TotalIndex == rhs.TotalIndex);
	}

	bool operator != (const BBIndex& rhs) const {
		return !(*this == rhs);
	}

	bool operator < (const BBIndex& rhs) const {
		return (TotalIndex < rhs.TotalIndex);
	}

	bool operator > (const BBIndex& rhs) const {
		return (TotalIndex > rhs.TotalIndex);
	}

	BBIndex operator+(const BBIndex& rhs) const {
		return BBIndex<ByteSizeVar>(0, TotalIndex + rhs.TotalIndex);
	}

	BBIndex& operator++() {
		if (BitIndex == (ByteSize - 1)) { ByteIndex++; BitIndex = 0; }
		else { BitIndex++; }
		return *this;
	}

	BBIndex operator++(int)
	{
		BBIndex old = *this;
		operator++();
		return old;
	}

	BBIndex& operator--() {
		if (BitIndex == 0) { ByteIndex--; BitIndex = ByteSize - 1; }
		else { BitIndex--; }
		return *this;
	}

	BBIndex operator--(int)
	{
		BBIndex old = *this;
		operator--();
		return old;
	}

};