//websocket
import io from 'socket.io-client';
const socket = io(process.env.VUE_APP_WEBSOCKET_URL);

socket.on('connect', function() {
  console.log("connected");
});

socket.on('disconnect', function() {});


export default function(store) {
  socket.on('game_list', data => {
    store.commit('setGameList', data)
  })
  store.subscribe(mutation => {
    if (mutation.type === 'setNickname') {
      socket.emit("enter_lobby", { player_name: mutation.payload });
    }
  })
}
