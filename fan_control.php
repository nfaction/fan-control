<!DOCTYPE HTML> 
<html>
<head>
<style>
.error {color: #FF0000;}
label {font-size: 1.5em;}
</style>
</head>
<body> 

<?php
// define variables and set to empty values
$fan = $setting = $command = "";
$fanErr = $settingErr = "";
if ($_SERVER["REQUEST_METHOD"] == "POST")
{
   if (!isset($_POST['fan'])){

    $fanErr = "* Fan selection is required";
  }
   else
     {
     $fan = test_input($_POST["fan"]);
      switch ($fan){
    case "living":
      $command = "1";
      break;
    case "dining":
      $command = "2";
      break;
    case "master":
      $command = "4";
      break;
    case "office":
      $command = "3";
      break;
    default:
      echo "Error!!! No Fan selected...";
      break;
  }
}
   
   if (!isset($_POST['setting'])){
      $settingErr = "* Setting is required";}
   else
     {
     $setting = test_input($_POST["setting"]);
     switch ($setting) {
    case "light":
      $command = $command . "s";
      break;
    case "foff":
      $command = $command . "o";
      break;
    case "low":
      $command = $command . "l";
      break;
    case "medium":
      $command = $command . "m";
      break;
    case "high":
      $command = $command . "h";
      break;
    default:
      echo "Error!!! No Setting chosen...";
      break;
  }
     }
}

function test_input($data)
{
     $data = trim($data);
     $data = stripslashes($data);
     $data = htmlspecialchars($data);
     return $data;
}
?>
<!-- Mobile browser formatter -->
<meta name="viewport" content="width=640" />

<h2>Fan Controller</h2>
<p><span class="error">* required field.</span></p>
    <form action='fan_control.php' method=post>
    <input id="01" type="radio" name="fan" value="living">
    <label for="01">Living Room</label><br>
    <input id="02" type="radio" name="fan" value="dining">
    <label for="02">Dining Room</label><br>
    <input id="03" type="radio" name="fan" value="master">
    <label for="03">Master Bedroom</label><br>
    <input id="04" type="radio" name="fan" value="office">
    <label for="04">Office</label><br>
    <span class="error"><?php echo $fanErr;?></span>
    <br>
    <input id="05" type="radio" name="setting" value="light">
    <label for="05">Light</label><br>
    <input id="06" type="radio" name="setting" value="foff">
    <label for="06">Fan Off</label><br>
    <input id="07" type="radio" name="setting" value="low">
    <label for="07">Fan Low</label><br>
    <input id="08" type="radio" name="setting" value="medium">
    <label for="08">Fan Medium</label><br>
    <input id="09" type="radio" name="setting" value="high">
    <label for="09">Fan High</label><br>
    <br>
    <input type="submit" name="submit" value="Submit"><br>
    <span class="error"><?php echo $settingErr;?></span>
    <br>
    <br>

    </form>
    <br>

<?php
echo "<h2>Debug data:</h2>";
echo $fan;
echo "<br>";
echo $setting;
echo "<br>";
echo "Command: $command";
  echo "<br>";
  echo "echo '$command' >> /dev/ttyUSB0";
  echo "<br>";
  $output = shell_exec("echo '$command' >> /dev/ttyUSB0");
  echo $output;
?>

</body>
</html>