
   <template>
     <md-snackbar md-position="center" :md-duration="8000" :md-active.sync="show2" md-persistent>
          <span>{{question}}</span>
          <md-button class="md-primary" @click="callback()">Ja</md-button>
        </md-snackbar>

   </template>

   <script>
   export default {
     name: 'WatsonSnackbar',
     props: {
       question: {type: String, default: "Willst Du dir deine Spielerfarbe aussuchen?"},
       onYes: Function
     },
     data: function() {
       return {show2: true}
     },
     methods: {
       callback: function() {
         this.onYes();
         this.show2 = false;
       }
     }
   }
   </script>
