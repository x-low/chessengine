var config = {
  draggable: true,
  position: 'start'
}

var board = Chessboard('board', config)

$('#setStartBtn').on('click', board.start)
