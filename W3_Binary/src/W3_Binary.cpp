#include "pch.h"

struct Float3f
{
	float X, Y, Z;
};

struct TeleportLocation
{
	bool IsActive;
	float X, Y, Z;
};

struct NPC
{
	std::string Name;
	float X, Y, Z;
};

void FirstExample()
{
	std::cout << "Example 1\n";
	std::cout << "=========\n\n";

	const std::string pod = std::is_pod<Float3f>::value == 1 ? "yes" : "no";
	std::cout << "Is the Float3 struct a pod: " << pod << "\n";

	Float3f toWrite;
	toWrite.X = 5.2f;
	toWrite.Y = 5.1f;
	toWrite.Z = 9.1f;

	std::ofstream temp;
	temp.open("example1.bin", std::ios::out | std::ios::binary);
	if (temp.is_open())
	{
		temp.write(reinterpret_cast<const char*>(&toWrite), sizeof toWrite);
		temp.close();
		std::cout << "Successfully wrote data to a binary file...\n";
	}

	Float3f toRead;
	std::ifstream input;
	input.open("example1.bin", std::ios::in | std::ios::binary);
	if (input.is_open())
	{
		input.read(reinterpret_cast<char*>(&toRead), sizeof toRead);
		assert(toRead.X == toWrite.X);
		assert(toRead.Y == toWrite.Y);
		assert(toRead.Z == toWrite.Z);
		input.close();
		std::cout << "Successfully read data from a binary file...\n";
	}

	std::cout << "Original float3 : [" << toWrite.X << ", " << toWrite.Y << ", " << toWrite.Z << "]\n";
	std::cout << "Read float3 : [" << toRead.X << ", " << toRead.Y << ", " << toRead.Z << "]\n";
}

void SecondExample()
{
	std::cout << "Example 2\n";
	std::cout << "=========\n\n";

	const std::string pod = std::is_pod<TeleportLocation>::value == 1 ? "yes" : "no";
	std::cout << "Is the TeleportLocation struct a pod: " << pod << "\n";

	TeleportLocation toWrite;
	toWrite.IsActive = true;
	toWrite.X = 5.2f;
	toWrite.Y = 5.1f;
	toWrite.Z = 9.1f;

	std::ofstream temp;
	temp.open("example2.bin", std::ios::out | std::ios::binary);
	if (temp.is_open())
	{
		temp.write(reinterpret_cast<const char*>(&toWrite), sizeof toWrite);
		temp.close();
		std::cout << "Successfully wrote data to a binary file...\n";
	}

	TeleportLocation toRead;
	std::ifstream input;
	input.open("example2.bin", std::ios::in | std::ios::binary);
	if (input.is_open())
	{
		input.read(reinterpret_cast<char*>(&toRead), sizeof toRead);
		assert(toRead.IsActive == toWrite.IsActive);
		assert(toRead.X == toWrite.X);
		assert(toRead.Y == toWrite.Y);
		assert(toRead.Z == toWrite.Z);
		input.close();
		std::cout << "Successfully read data from a binary file...\n";
	}

	std::cout << "Original TeleportLocation : [" << toWrite.IsActive << ", " << toWrite.X << ", " << toWrite.Y << ", " << toWrite.Z << "]\n";
	std::cout << "Read TeleportLocation : [" << toRead.IsActive << ", " << toRead.X << ", " << toRead.Y << ", " << toRead.Z << "]\n";

	std::cout << "Size of bool: " << sizeof(bool) << "\n";
	std::cout << "Size of float: " << sizeof(float) << "\n";
}

void ThirdExample()
{
	std::cout << "Example 3\n";
	std::cout << "=========\n\n";

	const std::string pod = std::is_pod<NPC>::value == 1 ? "yes" : "no";
	std::cout << "Is the NPC struct a pod: " << pod << "\n";

	NPC toWrite;
	toWrite.Name = "NPC1";
	toWrite.X = 5.2f;
	toWrite.Y = 5.1f;
	toWrite.Z = 9.1f;

	std::ofstream output;
	output.open("example3.bin", std::ios::out | std::ios::binary);
	if (output.is_open())
	{
		size_t size = toWrite.Name.size();
		output.write(reinterpret_cast<const char*>(&size), sizeof size);
		output.write(toWrite.Name.c_str(), size);
		output.write(reinterpret_cast<const char*>(&toWrite.X), sizeof toWrite.X);
		output.write(reinterpret_cast<const char*>(&toWrite.Y), sizeof toWrite.Y);
		output.write(reinterpret_cast<const char*>(&toWrite.Z), sizeof toWrite.Z);
		output.close();
		std::cout << "Successfully wrote data to a binary file...\n";
	}

	NPC toRead;
	std::ifstream input;
	input.open("example3.bin", std::ios::in | std::ios::binary);
	if (input.is_open())
	{
		size_t size;
		
		input.read(reinterpret_cast<char*>(&size), sizeof size);
		toRead.Name.resize(size);
		input.read(reinterpret_cast<char*>(&toRead.Name[0]), size);
		input.read(reinterpret_cast<char*>(&toRead.X), sizeof toRead.X);
		input.read(reinterpret_cast<char*>(&toRead.Y), sizeof toRead.Y);
		input.read(reinterpret_cast<char*>(&toRead.Z), sizeof toRead.Z);
		
		assert(toRead.Name == toWrite.Name);
		assert(toRead.X == toWrite.X);
		assert(toRead.Y == toWrite.Y);
		assert(toRead.Z == toWrite.Z);
		input.close();
		std::cout << "Successfully read data from a binary file...\n";
	}

	std::cout << "Original TeleportLocation : [" << toWrite.Name << ", " << toWrite.X << ", " << toWrite.Y << ", " << toWrite.Z << "]\n";
	std::cout << "Read TeleportLocation : [" << toRead.Name << ", " << toRead.X << ", " << toRead.Y << ", " << toRead.Z << "]\n";
}

int main(int argc, char* argv[])
{
	FirstExample();
	SecondExample();
	ThirdExample();

	return EXIT_SUCCESS;
}
