var chess = new Chess()
var $pgn = $('#pgn')

function onDragStart(source, piece, position, orientation) {
  if (chess.isGameOver())
    return false

  if ((chess.turn() === 'w' && piece.search(/^b/) !== -1) ||
      (chess.turn() === 'b' && piece.search(/^w/) !== -1))
    return false
}

function onDrop(source, target) {
  try {
    var move = chess.move({
      from: source,
      to: target,
      promotion: 'q'
    })
  } catch (invalidMove) {
      return 'snapback'
  }

  updateStatus()
}

function onSnapEnd() {
  board.position(chess.fen())
}

function updateStatus() {
  var status = ''

  var moveColour = 'White'
  if (chess.turn() === 'b')
    moveColour = 'Black'

  if (chess.isCheckmate())
    status = 'Game over, ' + moveColour + ' is in checkmate.'

  else if (chess.isDraw())
    status = 'Game over, drawn position'

  else {
    status = moveColour + ' to move'

    if (chess.inCheck())
      status += ', ' + moveColour + ' is in check'
  }

  $('#status').html(status)
  $('#pgn').html(chess.pgn())
}

var config = {
  draggable: true,
  position: 'start',
  onDragStart: onDragStart,
  onDrop: onDrop,
  onSnapEnd: onSnapEnd
}

board = Chessboard('board', config)
updateStatus()

$('#setStartBtn').on('click', board.start)
$('#flipOrientationBtn').on('click', board.flip);
