#pragma once

#include <glm/glm.hpp>
#include <fstream>

// expects values in pixelColor between 0.0 - 1.0. Will output incorrect color values otherwise. 
// Handle incorrect input values somehow? idk error or just ignore?
inline void writeColor(std::ofstream& out, const glm::vec3& pixelColor) {
	// for outputting to image convert to int range 0 - 255
	int r{ std::min(255, static_cast<int>(256 * pixelColor.x)) };
	int g{ std::min(255, static_cast<int>(256 * pixelColor.y)) };
	int b{ std::min(255, static_cast<int>(256 * pixelColor.z)) };

	out.put(static_cast<char>(r));
	out.put(static_cast<char>(g));
	out.put(static_cast<char>(b));
}