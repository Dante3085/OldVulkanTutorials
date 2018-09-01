// VulkanTutorial 8 vkEnumPhyDevVkPhysDe.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"
#include "vulkan\vulkan.h"
#include <iostream>

#define ASSERT_VULKAN(val) if(val != VK_SUCCESS) {__debugbreak();}		

/*"vkEnumeratePhysicalDevices & VkPhysicalDevice":

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen �ber das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weitere Struktur des Tutorials noch unbekannt ist.
3. Weitere Informationen, die unter genaue Punkte bzw. Themenbereiche zu fassen sind, werden wie folgt numeriert: "1. ... 1.1 ... 1.1.1 ... 2. ... 2.1 ... 2.1.1 ...".
-------------------------

Internetverweise
-----------------

-----------------

0. Die nun erschaffene Instance mit "instance_ONE" und "vkCreateInstance", erm�glicht den Zugriff auf Grafikkarten. Etappenziel: Logische Referenz auf eine Grafikkarte. 

1. In Vulkan gibt es 2 M�glichkeiten, um mit einer GPU zu kommunizieren.
	1.1 Logische Referenz: Wird aus physikalischer Referenz gebildet. Erm�glicht Rendern bzw. tats�chliches Arbeiten mit der Grafikkarte.
	1.2 Physikalische Referenz: Grafikkarte als Hardware wird in einem struct abgebildet. Properties k�nnen abgefragt werden (Speichermenge; Was kann die Karte ? etc.). Keine M�glichkeit zum Rendern.

2. "vkEnumeratePhysicalDevices()": 1. Parameter: instance (immer) 2. Parameter: Anzahl physical Devices 3. Parameter: Array mit physical Devices. Erf�llt 2 Funktionen.
	2.1 Wenn 3. Parameter "NULL" ist und 2. Parameter "Referenz an �berschreibbare Variable (uint32_t in diesem Fall)" enth�lt, wird in den physicalDeviceCount Pointer des 2. Parameters, die tats�chlich festgestellte
	Grafikkartenanzahl des Rechners gesteckt. Der Grund daf�r ist, dass man nie vorher wei�, wie viele Grafikkarten die Rechner, auf denen das Programm laufen soll, haben.
	2.2 Bef�llt "VkPhysicalDevice" Array, damit 3. Parameter nun pr�zise gef�llt werden kann.

	*1
	----
	reingegeben werden. Wichtig ist das man auch weniger reingeben kann, und somit Grafikkarten ausschlie�en kann.
	----

*/

namespace VulkanTutInstances {
	VkInstance instance_ONE;
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

	VkResult result = vkCreateInstance(&instanceInfo, NULL, &VulkanTutInstances::instance_ONE);	

	ASSERT_VULKAN(result);

	uint32_t amountOfPhysicalDevices = 0;
	result = vkEnumeratePhysicalDevices(VulkanTutInstances::instance_ONE, &amountOfPhysicalDevices, NULL);

	ASSERT_VULKAN(result);	//Wir �berpr�fen wieder, ob bei "vkEnumeratePhysicalDevices" alles richtig gelaufen ist.

	VkPhysicalDevice *physicalDevices = new VkPhysicalDevice[amountOfPhysicalDevices];		//Array, dass mit PhysicalDevices bef�llt wird und dann als 3. Parameter in "vkEnumeratePhysicalDevices" gegeben wird.
	
	result = vkEnumeratePhysicalDevices(VulkanTutInstances::instance_ONE, &amountOfPhysicalDevices, physicalDevices);	//Wenn 3.Parameter validen Pointer hat, kann hier in 2.Parameter "bis" festgestellte Deviceanzahl *1

	ASSERT_VULKAN(result);  //Wir �berpr�fen wieder, ob bei "vkEnumeratePhysicalDevices" alles richtig gelaufen ist.

	std::cout << amountOfPhysicalDevices;

	system("pause");
	return 0;
}

