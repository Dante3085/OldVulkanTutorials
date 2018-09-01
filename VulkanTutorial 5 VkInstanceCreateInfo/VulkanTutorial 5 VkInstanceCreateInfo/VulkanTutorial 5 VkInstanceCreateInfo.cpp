// VulkanTutorial 5 VkInstanceCreateInfo.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "vulkan\vulkan.h"



/*"VkInstanceCreateInfo":

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen über das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weitere Struktur des Tutorials noch unbekannt ist.
3. 
-------------------------

Internetverweise
-----------------

-----------------

1.Instance: Oberstes Element in Vulkan. Von dort werden unterschiedliche devices (Grafikkarten), pipelines geholt. Für eine Instance werden 2 Dinge benötigt. "Context" ist das Gegenstück zur Instance in OpenGL.
	1.2 VkInstanceCreateInfo:

		*1
		----
		"instanceInfo = {}" würde alle Attribute mit "0" initialisieren.
		----

		1.2.1 Layers: Sachen, die zwischen unterschiedlichen Bearbeitungsschritten reingeschaltet werden können. Zum Beispiel für "Debugging", "Profiling" und Teile des "Error Handlings". Später mehr...

		1.2.2 Extensions: Dinge, die die Funktionalität von Vulkan erweitern. Bevor Instance erstellt wird, sagen wir Vulkan welche Extensions eventuell benutzt werden. Je nach Extension müssen 
		diese dann noch "scharf gestellt" werden (damit ihr Effekt tatsächlich aktiviert wird). Dadurch das wir in Vulkan die verwendeten Extensions vor der Instance erwähnen, können alle nicht
		erwähnten Extensions später "komplett" ignoriert werden. In OpenGL ist dies nicht der Fall. Dort muss der Treiber für Extensions, die jeden Moment aktiviert werden könnten, essentielle 
		Bestandteile (Dinge, die die Extension braucht) tracken. Später mehr...
*/

int main() {
	


	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = NULL;
	appInfo.pApplicationName = "Vulkan Tutorial";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.pEngineName = "Super Vulkan Engine Turbo Mega";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceInfo;								//1.2_Alle Inhalte des structs müssen initialisiert werden, da sonst zufällige Werte aus dem Hauptspeicher Problemem machen könnten. *1
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;	//1.2_Muss immer auf "VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO" gesetzt werden. Grund: siehe Tutorial "4" -> VkApplicationInfo -> sType
	instanceInfo.pNext						= NULL;					//1.2_siehe Tutorial "4" -> VkApplicationInfo -> pNext
	instanceInfo.flags						= 0;					//1.2_Für "future Use" reserviert. Wird momentan nicht benötigt. Einfach = 0.
	instanceInfo.pApplicationInfo			= &appInfo;				//1.2_Pointer auf "VkApplicationInfo". Also = &appInfo.
	instanceInfo.enabledLayerCount			= 0;					//1.2_Gibt an wie viele Layer es gibt. Wir haben keine.
	instanceInfo.ppEnabledLayerNames		= NULL;					//1.2_Keine Layer.
	instanceInfo.enabledExtensionCount		= 0;					//1.2_Gibt an wie viele Extensions es gibt. Wir haben keine.
	instanceInfo.ppEnabledExtensionNames	= NULL;					//1.2_Keine Extensions.

	

    return 0;
}

