// VulkanTutorial 4 VkApplicationInfo.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"
#include "vulkan\vulkan.h"

/*"VkApplicationInfo":

Allgemeine Informationen
-------------------------
1. Das Sternchen mit einer Nummer ist ein Textverweis auf eine andere Kommentarstelle in dieser Datei. Erschaffen, weil zu wenig Platz in den 2-Bildschirmdimensionen :(.
2. Kommentare bei "0." sind meistens allgemeine Informationen �ber das Thema dieses Tutorials. Speziell zu dem Zeitpunkt, wo die weiter Struktur des Tutorials noch unbekannt ist.
-------------------------

Internetverweise
---------
"Void Pointer": http://www.learncpp.com/cpp-tutorial/613-void-pointers/
---------

0.Vulkan arbeitet immer mit "structs" (C-Klassen), da das Programm auch in C laufen soll. Alle Structnamen in Vulkan beginnen immer mit einem "Vk".

1.Instance: Oberstes Element in Vulkan. Von dort werden unterschiedliche devices (Grafikkarten), pipelines geholt. F�r eine Instance werden 2 Dinge ben�tigt.
	1.1 VkApplicationInfo: Beinhaltet Informationen �ber die Applikation. 
		*1:
		----
		In Vulkan haben alle structs einen "sType" am Anfang. Dieser beschreibt um was f�r einen struct es sich handelt. Grund: Auf noch tieferer Ebene (z.B. Kommunikation mit Treibern) wird 
		das Ganze als voidPointer �bergeben. Dieser hat keinerlei Informationen �ber seine Referenz bzw. was dahinter steckt. Dadurch das es in Vulkan zwingend notwendig ist, dass am Anfang immer
		der sType kommt, kann der Treiber trotzdem herausfinden, mit was er es zu tun hat, und entsprechend verfahren.
		----

		*2:
		----
		Major: Gro�e Spr�nge in der Programmentwicklung. Beispiel: Von Beta zu Release.
		Minor: Neue Features.
		Patch: Patches/Hotfixes.
		----

		*3
		----
		Grafikkarte muss mindestens Version 1_0 unterst�tzen.
		----
*/

int main() {

	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;			//1.1_Bei "VkApplicationInfo" muss "sType" immer auf "VK_STRUCTURE_TYPE_APPLICATION_INFO" gesetzt werden. *1
	appInfo.pNext = NULL;										//1.1_Tiefergreifend. Extensions, die die Funktionalit�t von Vulkan erweitern. Ben�tigen wir jetzt nicht, deswegen = NULL.
	appInfo.pApplicationName = "Vulkan Tutorial";				//1.1_Einfach der Name unserer/s Applikation/Programms.
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);		//1.1_Nicht einfach Zahl, sondern "VK_MAKE_VERSION". Kreiert Versionsnummer f�r Applikation. Format (Beispiel): 0.3.5 (Major.Minor.Patch). *2
	appInfo.pEngineName = "Super Vulkan Engine Turbo Mega";		//1.1_Einfach der Name unser eigenen Engine. Falls wir eine machen. Nicht dasselbe wie normale Applikation.
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);			//1.1_Versionsnummer f�r Engine. Siehe Kommentar zu "applicationVersion" f�r genauere Infos.
	appInfo.apiVersion = VK_API_VERSION_1_0;					//1.1_Versionsummer der Vulkan API. F�r "0" wird sie ignoriert. Momentan aktuelle und einzige Version "VK_API_VERSION_1_0". *3

    return 0;
}

