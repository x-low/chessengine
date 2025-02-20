var chess = new Chess()
var $pgn = $('#pgn')

function onDragStart(source, piece, position, orientation) {
  if (chess.chess_over())
    return false

  if ((chess.turn() === 'w' && piece.search(/^b/) !== -1) ||
      (chess.turn() === 'b' && piece.search(/^w/) !== -1))
    return false
}

function onDrop(source, target) {
  var move = chess.move({
    from: source,
    to: target,
    promotion: 'q' // always promote to queen
  })

  if (move === null)
    return 'snapback'
}

function updateStatus() {
  var status = ''

  var moveColour = 'White'
  if (chess.turn() === 'b')
    moveColour = 'Black'

  if (chess.in_checkmate())
    status = 'Game over, ' + moveColour + ' is in checkmate.'

  else if (chess.in_draw())
    status = 'Game over, drawn position'

  else {
    status = moveColour + ' to move'

    if (chess.in_check())
      status += ', ' + moveColour + ' is in check'
  }

  $status.html(status)
  $pgn.html(chess.pgn())
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
