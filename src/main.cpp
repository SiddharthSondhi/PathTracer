#include "Color.h"

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>

int main() {
	int imageWidth{ 1920 };
	int imageHeight{ 1080 };

	// For now outputting image using PPM Format: https://en.wikipedia.org/wiki/Netpbm
	std::ofstream outputFile{ "image.ppm" };

	outputFile << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

	for (int j{ 0 }; j < imageHeight; j++) {
		std::clog << "\rScanlines remaining: " << imageHeight - j;

		for (int i{ 0 }; i < imageWidth; i++) {
			// internally use float ranging from 0.0 to 1.0 to represent colors
			float r{ static_cast<float>(i) / (imageWidth - 1) };
			float g{ static_cast<float>(j) / (imageHeight - 1) };
			float b{ 1.0f };

			glm::vec3 pixelColor{ r, g, b };

			writeColor(outputFile, pixelColor);
		}

		outputFile << "\n";
	}

	std::clog << "\rDone.                          \n";
}