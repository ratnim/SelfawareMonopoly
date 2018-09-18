
   <template>
     <md-dialog :md-active.sync="show2">
       <md-dialog-title>Hi</md-dialog-title>
       <p>Wenn du nochmal würfelst willst, musst du nur hier klicken.</p>
       <!-- <div id="fb-root"></div>
<div class="fb-like" data-href="https://developers.facebook.com/docs/plugins/" data-layout="standard" data-action="like" data-size="large" data-show-faces="true" data-share="true"></div>

 -->

       <md-dialog-actions>
         <md-button class="md-primary" @click="show2 = false">Close</md-button>
         <md-button class="md-primary" @click="show2 = false">Save</md-button>
       </md-dialog-actions>
     </md-dialog>
 </template>


   <script>
   export default {
     name: 'WatsonDialog',
     props: {
       show: Boolean,
       question: {type: String, default: "Willst Du dir deine Spielerfarbe aussuchen?"},
       //onYes: Function,
       //onNo: Function
     },
     data: function() {
       return {show2: true}
     },
     mounted() {
       //let tag = document.createElement('img')
       //tag.onload = "onload=\"alert('test');this.parentNode.removeChild(this);\"";
    // (function(d, s, id) {var js, fjs = d.getElementsByTagName(s)[0];
    //   if (d.getElementById(id)) return;
    //   js = d.createElement(s); js.id = id;
    //   js.src = 'https://connect.facebook.net/de_DE/sdk.js#xfbml=1&version=v3.1&appId=1720802108194706&autoLogAppEvents=1';
    //   fjs.parentNode.insertBefore(js, fjs);
    // }(document, 'script', 'facebook-jssdk'));


    //recaptchaScript.setAttribute('src', 'https://www.google.com/recaptcha/api.js')
    //document.head.appendChild(recaptchaScript)
      }
   }
   </script>
