// VulkanTutorial ErrorhandlingVulkan.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "vulkan\vulkan.h"

#define ASSERT_VULKAN(val) if(val != VK_SUCCESS) {__debugbreak();}		//Makro, dass die Fehlerbehandlung streamlined. Eigentlich sollte "\" mehrere Zeilen ermöglichen, tut es aber nicht :(.

/*"Errorhandling in Vulkan":

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen über das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weitere Struktur des Tutorials noch unbekannt ist.
-------------------------

Internetverweise
-----------------
1. vkCreateInstance(3): https://www.khronos.org/registry/vulkan/specs/1.0/man/html/vkCreateInstance.html
2. VkResult(3)        : https://www.khronos.org/registry/vulkan/specs/1.0/man/html/VkResult.html
-----------------

1. Errorhandling: Nicht normales ExceptionHandling mit try/catch, sondern durch Returnwert einer Funktion (Fehlercode). Primitive Art des Exception Handling (Schneller als ExceptionHandling).

2. "vkCreateInstance()" Return Codes:
	2.1 "VK_SUCCESS"	                 korrekte Ausführung.
	2.2 "VK_ERROR_OUT_OF_HOST_MEMORY"    Host ist in diesem Fall C++. Nicht mehr genügend Speicherplatz im RAM (Beispiel:: Allocator).
	2.3 "VK_ERROR_OUT_OF_DEVICE_MEMORY"	 Device ist Grafikkarte. Grafikkarte hat nicht mehr genügend Speicher.
	2.4 "VK_ERROR_INITIALIZATION_FAILED" Vermutlich Zurückgabe, wenn kein anderer Errorcode zutrifft.
	2.5 "VK_ERROR_LAYER_NOT_PRESENT"     Nicht existierender Layer wurde angegeben.
	2.6 "VK_ERROR_EXTENSION_NOT_PRESENT" Nicht existierende Extension wurde angegeben.
	2.7 "VK_ERROR_INCOMPATIBLE_DRIVER"   Treiber ist inkompatibel mit unter Anderem der "VkApplicationInfo::apiVersion".

	*1
	----
	"VkResult" Instanzen speichern Return codes von Vulkan Kommandos (Funktionen).
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

	//VkInstance instance;					

	VkResult result = vkCreateInstance(&instanceInfo, NULL, &VulkanTutInstances::instance_ONE);	//Returnwert ist nicht das eigentlich createte(hier: Instance), sondern ein Fehlercode (Standard in Vulkan). *1

	//if (result != VK_SUCCESS) {
	//	__debugbreak();			//Visual Studio spezifische Fehlerbehandlung. Sorgt dafür, dass Ausführung des Codes hier gestoppt wird, falls Bedingung zutrifft.
	//}

	ASSERT_VULKAN(result);	//Falls Breakpoint ausgelöst wird, kann über "result" mit der Maus drübergegangen werden, um dessen Inhalt (Fehlercode) zu sehen.

	return 0;
}

