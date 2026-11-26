#include "Color.h"
#include "Ray.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>


glm::vec3 rayColor(const Ray& r, const Hittable& world);


int main() {
	// ------------------------------------ IMAGE ------------------------------------

	// For now outputting image using PPM Format: https://en.wikipedia.org/wiki/Netpbm
	std::ofstream outputFile{ "image.ppm", std::ios::binary };

	float aspectRatio{ 16.0f / 9.0f };
	int imageWidth{ 1920 };

	// use aspect ratio to calculate imageHeight, since it represent # of pixels, it must be an integer >= 1.
	int imageHeight{ static_cast<int>(imageWidth / aspectRatio) };
	imageHeight = imageHeight < 1 ? 1 : imageHeight;


	// ------------------------------------ WORLD ------------------------------------
	HittableList world;

	world.add(std::make_shared<Sphere>(glm::vec3{ 0.0f, 0.0f, -1.0f }, 0.5f));
	world.add(std::make_shared<Sphere>(glm::vec3{ 0.0f, -100.5f, -1.0f }, 100.0f));

	// ------------------------------------ CAMERA & VIEWPORT ------------------------------------
	// distance between camera and viewport
	float focalLength{ 1.0f }; 

	// Viewport represents screen in 3D space, this will be divided up into pixels and rays will be sent through to find color of each pixel
	// arbitrary height for now
	float viewportHeight{ 2.0 };
	// use the actual image width and height rather than ideal aspect ratio
	float viewportWidth{ viewportHeight * static_cast<float>(imageWidth) / imageHeight };
	
	glm::vec3 cameraPosition{ 0.0f };

	//vectors across the horizontal and down the vertical viewport edges
	glm::vec3 viewportU{ viewportWidth, 0.0f, 0.0f };
	glm::vec3 viewportV{ 0.0f, -viewportHeight, 0.0f };

	//horizontal and vertical distance between pixels
	glm::vec3 pixelDeltaU{ viewportU * (1.0f / imageWidth) };
	glm::vec3 pixelDeltaV{ viewportV * (1.0f / imageHeight) };

	glm::vec3 viewportTopLeftCorner{ cameraPosition + glm::vec3{0.0f, 0.0f, -focalLength} - (viewportU * 0.5f) - (viewportV * 0.5f) };
	
	// pixel on top left
	glm::vec3 topLeftPixelLoc{ viewportTopLeftCorner + 0.5f * (pixelDeltaU + pixelDeltaV) };

	
	// ------------------------------------ RENDER ------------------------------------

	outputFile << "P6\n" << imageWidth << " " << imageHeight << "\n255\n";

	for (int j{ 0 }; j < imageHeight; j++) {
		std::clog << "\rScanlines remaining: " << imageHeight - j;

		for (int i{ 0 }; i < imageWidth; i++) {
			glm::vec3 pixelCenter{ topLeftPixelLoc + (static_cast<float>(i) * pixelDeltaU) + (static_cast<float>(j) * pixelDeltaV) };
			glm::vec3 rayDirection{ pixelCenter - cameraPosition };
			Ray r{ cameraPosition, rayDirection };

			glm::vec3 pixelColor{ rayColor(r, world) };
			writeColor(outputFile, pixelColor);
		}
	}

	std::clog << "\rDone.                          \n";
}


glm::vec3 rayColor(const Ray& r, const Hittable& world) {
	HitRecord rec;

	if (world.hit(r, 0, std::numeric_limits<float>::infinity(), rec)) {
		return 0.5f * (rec.normal + glm::vec3{ 1.0f });
	}

	// range for a is [0.0 , 1.0] since r.direction is normalized
	float a{ 0.5f * (r.getDirection().y + 1.0f) };

	// lerp between white and blue using a
	return (1.0f - a) * glm::vec3{ 1.0f } + a * glm::vec3{ 0.2f, 0.4f, 1.0f };
}