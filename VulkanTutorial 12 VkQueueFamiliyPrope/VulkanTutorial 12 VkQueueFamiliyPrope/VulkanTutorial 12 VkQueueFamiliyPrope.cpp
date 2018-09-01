// VulkanTutorial 12 VkQueueFamiliyPrope.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "vulkan\vulkan.h"
#include <iostream>

#define ASSERT_VULKAN(val) if(val != VK_SUCCESS) {__debugbreak();}		

/*"VkQueueFamiliyProperties":

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen über das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weitere Struktur des Tutorials noch unbekannt ist.
3. Weitere Informationen, die unter genaue Punkte bzw. Themenbereiche zu fassen sind, werden wie folgt numeriert: "1. ... 1.1 ... 1.1.1 ... 2. ... 2.1 ... 2.1.1 ...".
-------------------------

Internetverweise
-----------------
1. VkQueueFamiliyProperties: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkQueueFamilyProperties.html
2. vkGetPhysicalDeviceQueueFamilyProperties: https://www.khronos.org/registry/vulkan/specs/1.0/man/html/vkGetPhysicalDeviceQueueFamilyProperties.html
3. 
-----------------

1. Queue: In Vulkan hat jede Grafikkarte unterschiedliche Queues, in denen man Tasks stapeln kann (Warteschlange für Aufgaben). GPU arbeitet dann Warteschlange nacheinander ab. Verschiedene Queues haben unterschiedliche
Eigenschaften. Diese Eigenschaften sind in "Queue Families" zusammengekapselt. Wichtig ist, dass die Queues alle parallel arbeiten können und somit für die Performance ausgenutzt werden sollten.
	1.1 Queue Familiy: Queues mit gleichen Eigenschaften bilden eine QueueFamily .Eine QueueFamily hat immer die gleichen Settings. Verschiedene Queues, die alle die gleichen Eigenschaften haben, aber parallel ablaufen 
	können. Es ist nicht festgelegt wie viele Queue Families eine Grafikkarte hat. Dies muss abgefragt werden. Um das zu tun siehe: "vkEnumeratePhysicalDevices" weiter unten (gleiche "Methode").

2. VkQueueFamilyProperties: Die Eigenschaften der Queue Families.
	2.1 queueFlags: Hat 4 Zustände, die angeben was die GPU eigentlich kann.
		2.1.1 VK_QUEUE_GRAPHICS_BIT: GPU kann "Grafik" berechnen.

		2.1.2 VK_QUEUE_COMPUTE_BIT: GPU kann CPU-ähnliche Berechnungen durchführen, die ausschließlich dem "Number Crunching" (Zahlenverarbeitung) dienen. 

		2.1.3 VK_QUEUE_TRANSFER_BIT: GPU kann Daten mit verschiedenen Instanzen austauschen (z.B.: GPU und CPU).

		2.1.4 VK_QUEUE_SPARSE_BINDING_BIT: Sparse Texturen. Eher unwichtig für uns momentan.

	2.2 queueCount: Wie viele Queues gibt es von dieser Queue Family.

	2.3 timestampValidBits: Bei Queues kann die aktuelle Zeit abgefragt werden (Profiling usw.). Gibt an wieviele Bits dieser timestamp genau ist. Falls "0", erlaubt die Queue keine timestamps. Falls nicht "0", mindestens
	"36", kann aber auch größer sein (aufgrund der Genauigkeit).

	2.4 minImageTransferGranularity: Für uns eher unwichtig. Hat was damit zutun, in wie vielen Blöcken man Images an die Grafikkarte übertragen kann. Ist "1, 1, 1", wenn "VK_QUEUE_GRAPHICS_BIT" und
	"VK_QUEUE_COMPUTE_BIT" auch auf "1" sind.

		*1
		----
		false. Nur falls beide eine Zahl außer "0" annehmen (true), ist der Ausdruck auch true.
		----
*/

namespace VulkanTutorial {

	/*INSTANCES*/
	VkInstance instance_ONE;

	/*FUNCTIONS*/
	void printDeviceStats(VkPhysicalDevice &device) {

		//Char Pointer that underlines Text in the console.
		char *underline = "--------------------------";

		/*VkPhysicalDeviceProperties
		-----------------------------*/

		std::cout << "PHYSICAL DEVICE PROPERTIES" << "\n" << underline << std::endl;

		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(device, &properties);

		std::cout << "Name: " << properties.deviceName << "\n";
		uint32_t apiVer = properties.apiVersion;
		std::cout << "apiVersion: " << VK_VERSION_MAJOR(apiVer) << "." << VK_VERSION_MINOR(apiVer) << "." << VK_VERSION_PATCH(apiVer) << "\n";
		std::cout << "deviceID: " << properties.deviceID << "\n";
		std::cout << "deviceType: " << properties.deviceType << "\n";
		std::cout << "driverVersion	: " << properties.driverVersion << "\n";
		std::cout << "pipelineCacheUUID: " << properties.pipelineCacheUUID << "\n";
		std::cout << "vendorID: " << properties.vendorID << "\n\n";
		//----------------------------

		/*VkPhysicalDeviceFeatures
		---------------------------*/

		std::cout << "PHYSICAL DEVICE FEATURES" << "\n" << underline << std::endl;

		VkPhysicalDeviceFeatures features;
		vkGetPhysicalDeviceFeatures(device, &features);

		std::cout << "Geometry Shader: " << features.geometryShader << "\n" << std::endl;
		//---------------------------

		/*VkPhysicalDeviceMemoryProperties
		---------------------------------*/

		std::cout << "PHYSICAL DEVICE MEMORY PROPERTIES" << "\n" << underline << std::endl;

		VkPhysicalDeviceMemoryProperties memoryProperties;
		vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);

		std::cout << "" << memoryProperties.memoryHeaps << "\n" << memoryProperties.memoryTypes << "\n\n";
		//---------------------------------

		/*VkQueueFamiliyProperties
		---------------------------*/

		std::cout << "QUEUE FAMILY PROPERTIES" << "\n" << underline << std::endl;

		uint32_t amountOfQueueFamilies = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &amountOfQueueFamilies, NULL);

		VkQueueFamilyProperties *familyProperties = new VkQueueFamilyProperties[amountOfQueueFamilies];

		vkGetPhysicalDeviceQueueFamilyProperties(device, &amountOfQueueFamilies, familyProperties);

		std::cout << "Amount of Queue Families: " << amountOfQueueFamilies << std::endl;

		for (int i = 0; i < amountOfQueueFamilies; i++) {
			std::cout << std::endl;
			std::cout << "Queue Familiy" << i << std::endl;
			std::cout << "VK_QUEUE_GRAPHICS_BIT " << ((familyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) << std::endl;	//Hier werden 2 Bits miteinander verglichen. Wenn ein Bit "0" (false) ist, dann ist der Ausdruck auch *1
			std::cout << "VK_QUEUE_COMPUTE_BIT " << ((familyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) != 0) << std::endl;
			std::cout << "VK_QUEUE_TRANSFER_BIT " << ((familyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) != 0) << std::endl;
			std::cout << "VK_QUEUE_SPARSE_BINDING_BIT " << ((familyProperties[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) != 0) << std::endl;
			std::cout << "Queue Count: " << familyProperties[i].queueCount << std::endl;
			std::cout << "Timestamp Valid Bits: " << familyProperties[i].timestampValidBits << std::endl;
			uint32_t width = familyProperties[i].minImageTransferGranularity.width;
			uint32_t height = familyProperties[i].minImageTransferGranularity.height;
			uint32_t depth = familyProperties[i].minImageTransferGranularity.depth;
			std::cout << "Min Image Transfer Granularity" << width << "," << height << "," << depth << std::endl;
		}

		std::cout << std::endl;
		delete[] familyProperties;
		//---------------------------
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

	VkResult result_ONE = vkCreateInstance(&instanceInfo, NULL, &VulkanTutorial::instance_ONE);

	ASSERT_VULKAN(result_ONE);

	uint32_t amountOfPhysicalDevices = 0;
	result_ONE = vkEnumeratePhysicalDevices(VulkanTutorial::instance_ONE, &amountOfPhysicalDevices, NULL);

	ASSERT_VULKAN(result_ONE);

	VkPhysicalDevice *physicalDevices = new VkPhysicalDevice[amountOfPhysicalDevices];	//WIRD SPÄTER AUFGERÄUMT.

	result_ONE = vkEnumeratePhysicalDevices(VulkanTutorial::instance_ONE, &amountOfPhysicalDevices, physicalDevices);

	ASSERT_VULKAN(result_ONE);

	for (int i = 0; i < amountOfPhysicalDevices; i++) {
		VulkanTutorial::printDeviceStats(physicalDevices[i]);
	}

	system("pause");
	return 0;

}


