// VulkanTutorial 11 VkPhysicalDeviceMem.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "vulkan\vulkan.h"
#include <iostream>

#define ASSERT_VULKAN(val) if(val != VK_SUCCESS) {__debugbreak();}		

/*"VkPhysicalDeviceMemoryProperties":

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen über das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weitere Struktur des Tutorials noch unbekannt ist.
3. Weitere Informationen, die unter genaue Punkte bzw. Themenbereiche zu fassen sind, werden wie folgt numeriert: "1. ... 1.1 ... 1.1.1 ... 2. ... 2.1 ... 2.1.1 ...".
-------------------------

Internetverweise
-----------------
1. VkPhysicalDeviceMemoryProperties: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkPhysicalDeviceMemoryProperties.html
2. VkMemoryType: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkMemoryType.html
3. VkMemoryPropertyFlags: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkMemoryPropertyFlags.html
-----------------

1. VkPhysicalDeviceMemoryProperties: Auf was für einen Speicher kann die Grafikkarte zugreifen und was kann dieser Speicher.
	1.1 VkMemoryType: Array an "memoryTypes". Beinhaltet "heapIndex", welcher sagt zu welchem Heap diese Properties gehören, und "propertyFlags".
		1.1.1 VkMemoryPropertyFlags: Zustände, die der Speicher haben kann. 
			1.1.1.1 "VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT": Wenn "propertyFlags" diesen Wert hat, ist der jeweilige Heapspeicher lokal zur GPU => Der Heap ist tatsächlich Grafikkartenspeicher.
			Falls "0", dann ist der Heap "Hostspeicher" (von der CPU oder vom RAM).

			1.1.1.2 "VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT": Wenn "propertyFlags" diesen Wert hat, ist Speicher für C++ Seite bzw. CPU sichtbar.

			1.1.1.3 "VK_MEMORY_PROPERTY_HOST_COHERENT_BIT": Bei Berechnungen im Computer, sowohl CPU als auch GPU, gibt es sogenannte "Caches". Berechnungen in den Caches sind schneller. Jedoch kann der jeweilige
			Cache immer nur von der CPU (Dann auch nur vom jeweiligen Kern.) bzw. der GPU (Häufig auch nur 1 Kern. Je nach Layer.) gesehen werden.
			Grafikkarte kann entweder nach jeder Berechnung alles wieder in den Hauptspeicher zurückschreiben (Sorgt dafür, dass CPU es sehen kann.), oder sie berechnet nur mit den Caches weiter.
			Das Gleiche gilt für die CPU. Falls "VK_MEMORY_PROPERTY_HOST_COHERENT_BIT" gesetzt ist, wird immer "geflushed" (Alle Änderungen sind sowohl für CPU als GPU sichtbar.). Falls nicht, dann nicht.

			1.1.1.4 "VK_MEMORY_PROPERTY_HOST_CACHED_BIT": Ob von der Host (C++ Seite) gecashed wurde, oder nicht.

			1.1.1.5 "VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT": Falls gesetzt, sorgt es dafür, dass der vom Programmierer allokierte Speicher nicht in voller Größe direkt allokiert wird, sondern sich von der Grafikkarte 
			nur gemerkt wird, "dieser Speicherblock wurde gerade allokiert", richtig allokiert sie den Speicherblock aber erst, wenn dieser vom Programm gebraucht wird. Wenn der GPU also gesagt wird, dort soll dieser
			Speicherblock allokiert werden, wird keine richtige Allokation gemacht, sondern der Grafikkarte nur der Hinweis gegeben, dass in naher Zukunft diese Menge an Speicher gebraucht werden könnte.
			Wenn nicht gesetzt, wird immer sofort allokiert.

	1.2 memoryTypeCount: Größe des "Array an "memoryTypes"".

	1.3 VkMemoryHeap: Array an "memoryHeaps". Hier liegt der Speicher tatsächlich drauf. Beinhaltet "VkDeviceSize" und "VkMemoryHeapFlags".

	1.4 memoryHeapCount: Größe des "Array an "memoryHeaps"". 
*/

namespace VulkanTutorial {

	/*INSTANCES*/
	VkInstance instance_ONE;

	/*FUNCTIONS*/
	void printDeviceStats(VkPhysicalDevice &device) {

		char *underline = "--------------------------";

		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(device, &properties);

		std::cout << "PHYSICAL DEVICE PROPERTIES" << "\n" << underline << std::endl;

		std::cout << "Name			   : " << properties.deviceName << "\n";
		uint32_t apiVer = properties.apiVersion;
		std::cout << "apiVersion	   : " << VK_VERSION_MAJOR(apiVer) << "." << VK_VERSION_MINOR(apiVer) << "." << VK_VERSION_PATCH(apiVer) << "\n";
		std::cout << "deviceID		   : " << properties.deviceID << "\n";
		std::cout << "deviceType	   : " << properties.deviceType << "\n";
		std::cout << "driverVersion	   : " << properties.driverVersion << "\n";
		std::cout << "pipelineCacheUUID: " << properties.pipelineCacheUUID << "\n";
		std::cout << "vendorID	       : " << properties.vendorID << "\n\n";

		VkPhysicalDeviceFeatures features;				
		vkGetPhysicalDeviceFeatures(device, &features);

		std::cout << "PHYSICAL DEVICE FEATURES" << "\n" << underline << std::endl;

		std::cout << "Geometry Shader: " << features.geometryShader << "\n" << std::endl;

		VkPhysicalDeviceMemoryProperties memoryProperties;
		vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);

		std::cout << "PHYSICAL DEVICE MEMORY PROPERTIES" << "\n" << underline << std::endl;




	}
}

int main() {

	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = NULL;
	appInfo.pApplicationName = "Vulkan Tutorial";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.pEngineName = "Super Vulkan Engine Turbo Mega";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceInfo;
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pNext = NULL;
	instanceInfo.flags = 0;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledLayerCount = 0;
	instanceInfo.ppEnabledLayerNames = NULL;
	instanceInfo.enabledExtensionCount = 0;
	instanceInfo.ppEnabledExtensionNames = NULL;

	VkResult result = vkCreateInstance(&instanceInfo, NULL, &VulkanTutorial::instance_ONE);

	ASSERT_VULKAN(result);

	uint32_t amountOfPhysicalDevices = 0;
	result = vkEnumeratePhysicalDevices(VulkanTutorial::instance_ONE, &amountOfPhysicalDevices, NULL);

	ASSERT_VULKAN(result);

	VkPhysicalDevice *physicalDevices = new VkPhysicalDevice[amountOfPhysicalDevices];

	result = vkEnumeratePhysicalDevices(VulkanTutorial::instance_ONE, &amountOfPhysicalDevices, physicalDevices);

	ASSERT_VULKAN(result);

	for (int i = 0; i < amountOfPhysicalDevices; i++) {
		VulkanTutorial::printDeviceStats(physicalDevices[i]);
	}

	system("pause");
	return 0;

}

