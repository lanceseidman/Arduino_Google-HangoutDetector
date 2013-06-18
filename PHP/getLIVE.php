<?php
// SET G+ API FEED
$GPlus_Key = ""; // Put your G+ API Key Here
$json = "https://www.googleapis.com/plus/v1/activities?query=hangout&key=" . $GPlus_Key;

$obj = json_decode(file_get_contents($json)); // Get & Store JSON API

foreach ($obj->items as $item) // Grab each "Title" Tag
{
	/* THIS IS A TEST TO SHOW YOU CAN SEARCH FOR A HANGOUT & OUTPUT BASICS TO IT...
	if($item->provider->title == "Hangout")
	{
		 echo "Found one...<br>";
		 echo $item->title . "<br>";
		 echo "This is actually a: " . $item->provider->title;
		 return;
	 }
    */
	 
 // Debug to see Titles: echo $item->title;
  if(!strpos($item->title,"SHOW AND TELL")) // No Show Title Exists!
  {
   // print "Offline"; // Report no Possible Match...
   echo "0"; // Means OFFLINE
    return; // Stop looking...
  }
  else // Show Title DOES Exist!
  {
   // Debug to see ID: echo $item->id;
	if($item->id == "1") // Replace with your G+ ID (Current is AdaFruit)
	 { 
		  if($item->provider->title == "Hangout") // Make sure it's not a Post Talking about a Hangout...
		  {
			  // echo "On Air"; // G+ Hangout is Active!
			  echo "1"; // Means ONLINE
			   return;
		  }
	 } 
	else // Turns out no Hangout we want...
	 {
	  //echo "Offline"; // Turns out it was a False Alarm (Someone else)!
	  echo "0"; // Means OFFLINE
	  return;
	 }
  }
}
?>
