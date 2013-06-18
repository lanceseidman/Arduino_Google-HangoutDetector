*/
* TITLE: Arduino Google+ Hangout Detector
* AUTHOR: Lance Seidman <@LanceSeidman; http://lance.compulsivetech.biz>
* WARNING: THIS IS USED WITH THE GOLIVE.PHP FILE. THE PHP FILE USES THE HTTPS API FROM GOOGLE.
* 
* WHY NOT GO FOR THE API ITSELF? ... NO HTTPS???
* COULD WE USE HTTPS WITH ARDUINO? TECHNICALLY, YES BUT IT WOULD BE HUGE & TERRIBLE 
* SO THIS IS THE NEXT BEST THING... 
*
* WHY BUILD THIS?
* I MADE THIS IN A FEW DAYS FOR THE FOLKS AT ADAFRUIT, TRYING TO DO WHAT LADYADA WANTED,
* AN ARDUINO BASED API GRABBER... UNFORTUNATELY HAD TO MAKE IT A LITTLE LESS COOL AS THE
* GOOGLE+ API REQUIRES HTTPS ONLY, NO HTTP.
*
* ISSUES. WARRANTY. CONTACT FOR SUPPORT.
* THE WHOLE PROJECT IS "AS-IS" AND HAS A ZERO WARRANTY WITH IT. IT'S OPEN TO THE PUBLIC TO
* BE USED AS HE/SHE DESIRES. IF YOU FIND A FLAW, I HAVE TOO BUT LIKELY NOT THE SAME THING
* SO GO FORTH AND FILE A SUPPORT TICKET. YOU CAN ALWAYS FOLLOW ME ON TWITTER IF YOU NEED
* ME FOR ANYTHING (@LANCESEIDMAN).
*
* DIRECTIONS
* ----------
* 1). UPLOAD goLIVE.php TO A WEB HOST OR LOCAL HTTPD/PHP BOX (EVEN USE A RASPBERRY PI).
* 2). EDIT: G_API[], GET (/path-to-getLIVE.php), & Host (www.your-server-name.com).
* 3). OPTIONAL EDIT: IP_ADD (Set a Specific Local IP) or MAC_ADD (Set a Specific MAC Address).
*
* PS... WHY IS aJSON HERE IF NO JSON IS USED?
* IN MY OTHER PROJECTS, I WAS ASKED HOW DO I USE JSON? SO, I INCLUDED MOST OF WHAT YOU NEED
* TO KNOW IN ORDER TO GET STARTED WITH aJSON (CAN BE FOUND ON GITHUB).
*
*/

// #include <aJSON.h> - NOT USED SINCE HTTPS API. 
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
char G_API[] = "www.your-server-name.com"; 
// char rtnchar[500]; - NOT USED; NORMALLY FOR OUR JSON API
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
  client.println("GET /path-to-getLIVE.php HTTP/1.1");
  client.println("Host: www.your-server-name.com"); // Would be GoogleAPIS.com; Insert Domain Hosting PHP File.
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
    // Use for Debug: Serial.println(incoming);
    if(incoming == '0')
    {
      Serial.println("No Hangout Found...");
      delay(50000);
    }

    // THIS IS A TERRIBLE WAY TO GO BUT WE ONLY HAVE A OFFLINE (0) or ON AIR (1)
    else
    {
      Serial.println("Hangout Found!");
      
      delay(50000);
    }
    
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

