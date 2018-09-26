

<template>

<md-snackbar md-position="center" :md-duration="8000" :md-active.sync="show2">
    <span>{{question}}</span>
    <md-button class="md-primary" @click="callback()">Ja</md-button>
</md-snackbar>

</template>

<script>

export default {
    name: 'WatsonSnackbar',
    props: {
        onYes: Function
    },
    data: function() {
        return {
            show2: false,
            question: "?"
        }
    },
    methods: {
        show: function(question) {
            this.question = question;
            this.show2 = true;
        },
        hide: function() {
            this.show2 = false;
        },
        callback: function() {
            this.show2 = false;
            setTimeout(this.onYes, 100);
        }
    }
}

</script>
