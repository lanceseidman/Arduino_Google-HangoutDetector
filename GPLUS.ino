#include <aJSON.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Dhcp.h>
#include <Dns.h>
#include <EthernetUdp.h>
#include <util.h>

// LET'S SETUP WHAT WE'LL NEED...
int led = 8; // Use: LED to Flash
// Create a MAC Address for our Device
byte MAC_ADD[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFE};
// Define a IP for our Device
IPAddress IP_ADD (192,168,0,188);
// Setup to use Client via Ethernet Lib
EthernetClient client;
// Since G+ API IS HTTPS use the getLIVE.php Script & Upload to your Server/Pi 
char G_API[] = "www.wearingdigital.com"; 
char G_API1[] = "www.your-server-name.com"; 
char rtnchar[500];
/*
WE HAVE NO USE FOR JSON HERE... BUT DEFINE FOR OTHER API'S
char rtnchar[500];
int chpos = 0;
aJsonObject* root; 
*/

void setup()
{
  Serial.begin(9600);    // Set up Serial @ 9600
  Serial.println("Google+ Hangouts OnAir Search Active...");
  
  pinMode(led, OUTPUT); // Setup LED
  
  if (Ethernet.begin(MAC_ADD) == 0) {
    Serial.println("DHCP FAILED... Trying new Method...");
    Ethernet.begin(MAC_ADD, IP_ADD);
  }
  delay(1000); // Wait for Ethernet Shield to Activate... 

// SINCE WE HAVE TO USE THE getLIVE.php Script, THIS IS A LIE...
  Serial.println("Going to connect to G+ Activities...");
  
  if(client.connect(G_API, 80)) // Connect to G+ API...
  { 
  // Connected... Let's perform a Request...
  Serial.println("Connected to API..."); // Assume we are connected. 
  /* SINCE API IS HTTPS, BELOW IS USELESS
  client.println("GET /plus/v1/activities?query=hangout&maxResults=5&key= HTTP/1.1");
  */
  client.println("GET /lab/getLIVE.php HTTP/1.1");
  client.println("Host: www.wearingdigital.com"); // Would be GoogleAPIS.com
  /*
    client.println("GET /path-to-getLIVE.php HTTP/1.1");
  client.println("Host: www.your-server-name.com"); // Would be GoogleAPIS.com
  */
  client.println("Connection: close");
  client.println();
  }
 else // Not looking good here...
 {
   // Let's tell them we didn't make our Request...
   Serial.println("Error in Requesting Status...");
 }
   
}
 
void loop()
{
  FindHangout();
}
void FindHangout()
{
  if(client.available()) // We have a Connection!
  {
    char incoming = client.read(); // Store Available Data to incoming
   // Serial.println(incoming);
   //rtnchar[0] = incoming;
    if(incoming == '0')
    {
      Serial.println("No Hangout Found...");
      delay(50000);
    }
    Serial.print(incoming);
    // THIS IS A TERRIBLE WAY TO DO BUT WE ONLY HAVE A OFFLINE or ON AIR
   /* else
    {
      Serial.println("Hangout Found!");
      
      delay(50000);
    }*/
    
    /*
    SINCE WE CAN'T USE G+ API... THIS IS USELESS...
    if(incoming == '{')
    {
      //found JSON
    }
    
    rtnchar[chpos] = incoming;
    ++chpos;
    Serial.print(incoming);
    */

  }
}

