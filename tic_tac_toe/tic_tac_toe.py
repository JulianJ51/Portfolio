def print_board(game_board):
	print("   1 2 3")
	let = 'A'
	for row in game_board:
		print(let, end="  ")
		let = chr(ord(let) + 1)
		for element in row:
			print(element, end=" ")
		print()

def change_board(game_board, move, symbol):
	row = (ord(move[0]) - 64)
	game_board[int(row) - 1][int(move[1]) - 1] = symbol

def opp_move(game_board, socket, opp_symbol):
	print("Waiting for opponent's move. Don't type anything!")
	opp_move = socket.recv(1000)
	change_board(game_board, opp_move.decode(), opp_symbol)
	return opp_move.decode()

def player_move(game_board, socket, u_symbol, opp_move):
	print_board(game_board)
	move = input(f"Your opponent played {opp_move}, your move([ABC][123]): ")
	move = move_valid(game_board, move)
	change_board(game_board, move, u_symbol)
	print_board(game_board)
	socket.send(move.encode())

def game_over(game_board, u_symbol, opp_symbol):
	for row in game_board:
		#check if user won in columns
		if row[0] == row[1] == row[2] == u_symbol:
			print("Congratulations, you won!")
			return True
		#check if opponent won in columns
		elif row[0] == row[1] == row[2] == opp_symbol:
			print("Your opponent won the game!")
			return True
	for i in range(2):
		if game_board[0][i] == game_board[1][i] == game_board[2][i] == u_symbol:
			print("Congratulations, you won!")
			return True
		elif game_board[0][i] == game_board[1][i] == game_board[2][i] == opp_symbol:
			print("Your opponent won the game!")
			return True
	#check Diagonals
	if game_board[0][0] == game_board[1][1] == game_board[2][2] == u_symbol:
		print("Congratulations, you won!")
		return True
	elif game_board[0][0] == game_board[1][1] == game_board[2][2] == opp_symbol:
		print("Your opponent won the game!")
		return True
	elif game_board[2][0] == game_board[1][1] == game_board[0][2] == u_symbol:
		print("Congratulations, you won!")
		return True
	elif game_board[2][0] == game_board[1][1] == game_board[0][2] == opp_symbol:
		print("Your opponent won the game!")
		return True
	#check tie
	elif not(any('.' in sublist for sublist in game_board)):
		print(("It's a tie!"))
		return True
	
def move_valid(game_board, move):
	while ((move != "A1") and (move != "A2") and (move != "A3") and
		(move != "B1") and (move != "B2") and (move != "B3") and
		(move != "C1") and (move != "C2") and (move != "C3")):
		move = input("Invalid input, try again...")
	while (game_board[int(ord(move[0]) - 64) - 1][int(move[1]) - 1]) != "." and move[1] <= 0:
		move = input("Invalid Input, try again...")
	
	return move


