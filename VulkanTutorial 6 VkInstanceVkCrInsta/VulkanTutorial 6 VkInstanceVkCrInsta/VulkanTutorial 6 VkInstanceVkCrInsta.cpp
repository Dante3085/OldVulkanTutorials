// VulkanTutorial 6 VkInstanceVkCrInsta.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "vulkan\vulkan.h"

/*"VkInstance&vkCreateInstance": 

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen über das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weitere Struktur des Tutorials noch unbekannt ist.
3.
-------------------------

Internetverweise
-----------------

-----------------

0. Funktionen fangen in Vulkan immer mit "vk" an. Structs mit "Vk".

1.Instance: Oberstes Element in Vulkan. Von dort werden unterschiedliche devices (Grafikkarten), pipelines geholt. Für eine Instance werden 2 Dinge benötigt. "Context" ist das Gegenstück zur Instance in OpenGL.
			Vorbereitung, um überhaupt mit Vulkan arbeiten zu können. Sollte global sein, da häufiger gebraucht. In echtem Projekt in Namespace. Es kann vorkommen, dass mehrere Instances gebraucht werden. Beispiel:
			2 Programme mit "VkInstance" und 3. Programm, dass die anderen gleichzeitig aufruft.
	*1
	----
	"NULL" sagt Vulkan, dass wir keinen eigenen Allokator haben. Somit wird der Vulkan interne Allokator verwendet. 3.Parameter: Pointer auf "VkInstance".
	----

*/

namespace VulkanTutInstances {	//Vulkan Tutorial Instances.
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

	//VkInstance instance;					//Dummywert, der an "vkCreateInstance()" gegeben wird. vkCreateInstance macht daraus etwas für uns brauchbares. Gehört eigentlich global und in Namespace.

	vkCreateInstance(&instanceInfo, NULL, &VulkanTutInstances::instance_ONE);	//1. Parameter: Pointer auf "VkInstanceCreateInfo". 2. Parameter: Allokator (ermöglicht das Erstellen von Code ähnlich zu "new" und "malloc"/Speicherallokation). *1

    return 0;
}

