const char home[] PROGMEM = R"=====(
<!doctype html>
<html lang="en">

<head>
	
<style>

body {
    color: #777;
}

.pure-img-responsive {
    max-width: 100%;
    height: auto;
}

/*
Add transition to containers so they can push in and out.
*/

/*
This is the parent `<div>` that contains the menu and the content area.
*/


/*
The content `<div>` is where all your content goes.
*/
.content {
    margin: 0 auto;
    padding: 0 2em;
    max-width: 800px;
    margin-bottom: 50px;
    line-height: 1.6em;
}

.header {
     margin: 0;
     color: #333;
     text-align: center;
     padding: 2.5em 2em 0;
     border-bottom: 1px solid #eee;
 }
   





@media (prefers-color-scheme: light) {
  :root {
    --color-bg: #ffffff;
    --color-fg: #000000;
  }
}
 
@media (min-width: 48em) {


    .content {
        padding-left: 2em;
        padding-right: 2em;
    }

    #layout {
        padding-left: 0px; /* left col width "#menu" */
        left: 0;
    }
 
}

@media (max-width: 48em) {
    #layout.active {
        position: relative;
        left: 150px;
    }
}
    </style>



<style>
    .btn{
        background-color:green;
        color: white;
        width: 50%;
        height: 40px;
    }
    .btn:hover{
        background-color: #092c3e;
    }

    input[type="checkbox"]{
        -webkit-appearance: none;
        visibility: hidden;
         display: none;

      
    }
    .check{
        position: relative;
        display: block;
        width:50px ;
        height: 30px;
        background: #092c3e;
        cursor: pointer;
        border-radius: 110px;
        overflow: hidden;
        /* transition:0.3s; */
       /* text-align: center; */
    }

    .d{
        /* top: 5px; */
        position: relative;
        right: 30px;
        bottom: -20px;
        float:right;
    }
    input[type="checkbox"]:checked ~ .check  {
        background: #fff;
        box-shadow: 0 0 0 1900px #092c3e;
        z-index: -1;
        

    }
    .check:before{
        content: '';
        position: absolute;
        top: 2px;
        left: 2px;
        background: #fff ;
        width: 25px;
        height: 25px;
        border-radius: 50%;
        transition: 1s;

        
    }
    input[type="checkbox"]:checked ~ .check::before {
    transform: translateX(-50px);
    }

    .check:after{
        content: '';
        position: absolute;
        top: 2px;
        left: 2px;
        background: #000 ;
        width: 25px;
        height: 25px;
        border-radius: 50%;
        transition: 0.5s;
        transform: translateX(50px);
        
    }
    input[type="checkbox"]:checked ~ .check:after {
        transform: translateX(0px);
    }

 
h2{
    /* position: relative; */
    font-size: 3em;
    color: #000;
    /* opacity: 0.5; */
}
h2:before{
    content: attr(data-text);
    position: absolute;
    background-image: linear-gradient(yellow,green);
    color: transparent;
    background-clip: text;
    -webkit-background-clip: text;
    width: 270px;
    overflow: hidden;
    white-space: nowrap;
    border-right: 4px solid green;
    animation: animate 8s linear infinite;
}
@keyframes animate{
    0%
    {
        width: 0;
    }

}


.inpt{
  width: 70%;
  padding: 15px;
  margin: 5px;
  border: 1px solid #ccc;
  border-radius: 4px;
  text-align: center;
  /* resize: vertical; */
/* justify-content: center; */
}


input[type=submit] {
  background-color: #04AA6D;
  color: white;
  padding: 12px 20px;
  border: none;
  border-radius: 4px;
  cursor: pointer;
  text-align: center;
  float: right;
}

input[type=submit]:hover {
  background-color: #45a049;
}

.container {
  border-radius: 5px;
  background-color: #f2f2f2;
  padding: 20px;
}

.col-25 {
  float: left;
  width: 25%;
  margin-top: 6px;
}

.col-75 {
  /* float: left; */
  text-align: center;
  width: 100%;
  margin-top: 6px;
}

/* Clear floats after the columns */
.row:after {
  content: "";
  display: table;
  clear: both;
}

/* Responsive layout - when the screen is less than 600px wide, make the two columns stack on top of each other instead of next to each other */
@media screen and (max-width: 600px) {
  input[type=submit] {
    /* text-align: center; */
    /* width: 90%; */
    margin-top: 10;
    /* float: right; */
    right: 80px;
    /* left: -20px; */
  }
  input[type=text]{
    text-align: center;
  }
  .container{
    text-align: center;
  }
  .row{
    text-align: center;
  }
}

.clock {
        font-size: 40px;
        margin-bottom: -10px;
        background: -webkit-linear-gradient(green, green);
        -webkit-background-clip: text;
        -webkit-text-fill-color: transparent;
        /* font-weight: 500; */
        /* display: block; */
        width: 20%;
        height: 20%;
        display: inline;
        padding: 10px 1px;
      }
</style>

</head>

<body >
	<div id="layout">
		

		<div id="main" >
            <label class="d"><input type="checkbox" ><span class="check"></span></label>
			<div class="header">
            
				<h2 data-text="Sihab Embuns 369">Sihab Embuns 369</h2>
           
				
			</div>
			<div class="content" >
				<br>
                <div style="text-align: center;">
                <input type="radio" value="jm" name="a" onChange="change(this)">Jam
                <input type="radio" value="wf" name="a" onChange="change(this)">Wifi
                <input type="radio" value="bt" name="a" onChange="change(this)">Bluetooth
            </div><br>
            <div class="container" hidden id="wifi">
                <form action="/setwifi" method="post">
                  <div class="row">
                    <div class="col-75">
                        <span id="waringssid" ></span><br>
                      <input type="text" class="inpt" oninput="changewifi()" id="ssid"  name="ssid" placeholder="Ganti SSID" required>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col-75">
                      <input type="text" class="inpt"  oninput="changewifi()" id="pswd" name="pswd" placeholder="Ganti Password" required>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col-75">
                    <button id="btn"class="btn"  type="submit" style="text-align: center;" onclick="gantiwifi()" hidden>Ganti</button>
                  </div>
                </div>
                </form>
                <h5>
                    note: SSID/nama wifi dan password tidak boleh dari 10 huruf/karakter
                    </h5>
              </div>


              <div class="container" hidden id="bluetooth">
                <form action="/setbt" method="post">
                  <div class="row">
                    <div class="col-75">
                        <span id="waringssidbt" ></span><br>
                      <input type="text" class="inpt"  oninput="changebt()" id="btt" name="btt" placeholder="Ganti Bluetooth" required>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col-75">
                    <button id="btnbt" class="btn"  type="submit" style="text-align: center;" onclick="gantibt()" hidden>Ganti</button>
                  </div>
                </div>
                </form>
                <h5>
                    note: Nama Bluetooth tidak boleh dari 10 huruf/karakter
                    </h5>
              </div>
                  <div class="container" hidden id="jamm">
                  <div style="text-align: center;">
                          <!-- <span id="waringssidbt" ></span><br> -->
                          <h3>Jam sekarang:</h3>
                          <h1 id="jam" class="clock" value="jam" name="jam"></h1>
                          <h1 id=":" class="clock">:</h1>
                          <p id="menit" class="clock" name="menit"></p>
                          <p id=":" class="clock">:</p>
                          <p id="detik" class="clock" name="detik"></p><br>
                          <button class="btn" onclick="updatejam()">Update jam otomatis</button>
                  </div><br>
                    <form action="/setjam" method="post">
                      <div class="row">
                        <div class="col-75">
                                <input type="number" class="inpt" name="jam" class="inp" id="jam" placeholder="Set jam disini"><br>
                                <input type="number" class="inpt" name="menit" class="inp" id="menit" placeholder="Set menit disini"></br>
                
                        </div>
                      </div>
                      <div class="row">
                        <div class="col-75">
                            <button name="klik" value="1" onclick="updatemanual()" class="btn"> Update jam manual </button><br>
                      </div>
                    </div>
                    </form>
               
                  </div>
                 
			</div>
       
		</div>
	</div>

    <script>

     setInterval(customClock, 500);
        function customClock() {
          var time = new Date();
          var hrs = time.getHours();
          var min = time.getMinutes();
          var sec = time.getSeconds();
    
        //    document.getElementById('clock').innerHTML = hrs + ":" + min + ":" + sec; 
          document.getElementById('jam').innerHTML = hrs;
          document.getElementById('menit').innerHTML = min;
          document.getElementById('detik').innerHTML = sec;
        }

        function gantiwifi(){
    p =  document.getElementById("ssid").value
                   z = document.getElementById("pswd").value
     //             nocache = \"/&nocache=\" + Math.random() * 1000000;
            var request = new XMLHttpRequest();
            request.open("POST",+ p + z , false);
             request.send(null);  
   }

   function updatemanual() {
          x = document.getElementById("jam").value
          y = document.getElementById("menit").value
          z = document.getElementById("klik").value
          //  nocache = \"/&nocache=\" + Math.random() * 1000000;
          var request = new XMLHttpRequest();
          request.open("POST", + x + y + z, false);
          request.send(null);
    
        }

         
        function updatejam() {
          x = document.getElementById("jam").innerHTML
          y = document.getElementById("menit").innerHTML
          z = document.getElementById("detik").innerHTML
          
          console.log(z);
          request = new XMLHttpRequest();
          request.open("POST", 'setjam?jam='+ x +'&menit='+ y +'&detik='+ z, false);
          request.send(null);
        }

   function gantibt(){
 p =  document.getElementById("btt").value
     //             nocache = \"/&nocache=\" + Math.random() * 1000000;
            var request = new XMLHttpRequest();
            request.open("POST",+ p, false);
             request.send(null);  
     
   }
        function changewifi() {
            let sside = document.getElementById('ssid').value
            let pswd = document.getElementById('pswd').value
            
            // console.log(sside);
            if (sside.length >10) {
                const element = document.querySelector('#waringssid');
                element.style.color = "red";
                element.innerHTML = "SSID lebih dari 10 karater/kata"
                document.getElementById("btn").hidden = true
    
                // document.getElementById('ssid').value = ""
            }else if(sside.length == 10){
                const element = document.querySelector('#waringssid').innerHTML = "";
                document.getElementById("btn").hidden = false
            }else{
                document.getElementById("btn").removeAttribute("hidden")
            }
    
            if (pswd.length >10) {
                const element = document.querySelector('#waringssid');
                element.style.color = "red";
                element.innerHTML = "Password lebih dari 10 karater/kata"
                document.getElementById("btn").hidden = true
                // document.getElementById('pswd').value = ""
            }else if(pswd.length == 10){
                const element = document.querySelector('#waringssid').innerHTML = "";
                document.getElementById("btn").hidden = false
            }else{
                document.getElementById("btn").removeAttribute("hidden")
            }
    
            if (sside.length > 10 && pswd.length >10 ) {
                document.getElementById("btn").hidden = true
                const element = document.querySelector('#waringssid');
                element.style.color = "red";
                element.innerHTML = "SSID dan Password lebih dari 10 karater/kata"
            }else if (sside.length == 0 || pswd.length == 0) {
                document.getElementById("btn").hidden = true
            }
        }
        function changebt() {
            let bt= document.getElementById('btt').value
            if (bt.length >10) {
                const element = document.querySelector('#waringssidbt');
                element.style.color = "red";
                element.innerHTML = "Nama Blutooth lebih dari 10 karater/kata"
                document.getElementById("btnbt").hidden = true
    
                // document.getElementById('ssid').value = ""
            }else if(btt.length == 10){
                const element = document.querySelector('#waringssidbt').innerHTML = "";
                document.getElementById("btnbt").hidden = false
            }else{
                document.getElementById("btnbt").removeAttribute("hidden")
            }
        }
    
    
    
                function change(a) {
                  if (a.value == "wf") {
                    document.getElementById("wifi").hidden = false
                    document.getElementById("bluetooth").hidden = true
                    document.getElementById("jamm").hidden =  true

                  }else if(a.value == "bt"){
                    document.getElementById("wifi").hidden = true
                    document.getElementById("bluetooth").hidden = false
                    document.getElementById("jamm").hidden =  true
                  }else if(a.value == "jm"){
                    document.getElementById("wifi").hidden = true
                    document.getElementById("bluetooth").hidden = true
                    document.getElementById("jamm").hidden =  false
                  }
                }
    </script>
</body>


</html>


    )=====";