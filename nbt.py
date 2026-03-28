"""
This is a simple python program that demonstrates how to run KataGo's
analysis engine as a subprocess and send it a query. It queries the
result of playing the 4-4 point on an empty board and prints out
the json response.
"""

import argparse
import json
import subprocess
import time
from threading import Thread
import sgfmill
import sgfmill.boards
import sgfmill.ascii_boards
from typing import Tuple, List, Optional, Union, Literal, Any, Dict

Color = Union[Literal["b"],Literal["w"]]
Move = Union[None,Literal["pass"],Tuple[int,int]]

def sgfmill_to_str(move: Move) -> str:
    if move is None:
        return "pass"
    if move == "pass":
        return "pass"
    (y,x) = move
    return "ABCDEFGHJKLMNOPQRSTUVWXYZ"[x] + str(y+1)

class KataGo:

    def __init__(self, katago_path: str, config_path: str, model_path: str, additional_args: List[str] = []):
        self.query_counter = 0
        katago = subprocess.Popen(
            [katago_path, "analysis", "-config", config_path, "-model", model_path, *additional_args],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        self.katago = katago
        def printforever():
            while katago.poll() is None:
                data = katago.stderr.readline()
                time.sleep(0)
                if data:
                    print("KataGo: ", data.decode(), end="")
            data = katago.stderr.read()
            if data:
                print("KataGo: ", data.decode(), end="")
        self.stderrthread = Thread(target=printforever)
        self.stderrthread.start()

    def close(self):
        self.katago.stdin.close()


    def query(self, initial_board: sgfmill.boards.Board, moves: List[Tuple[Color,Move]], komi: float, max_visits=None):
        query = {}

        query["id"] = str(self.query_counter)
        self.query_counter += 1

        query["moves"] = [(color,sgfmill_to_str(move)) for color, move in moves]
        query["initialStones"] = []
        for y in range(initial_board.side):
            for x in range(initial_board.side):
                color = initial_board.get(y,x)
                if color:
                    query["initialStones"].append((color,sgfmill_to_str((y,x))))
        query["rules"] = "Chinese"
        query["komi"] = komi
        query["boardXSize"] = initial_board.side
        query["boardYSize"] = initial_board.side
        query["includePolicy"] = True
        if max_visits is not None:
            query["maxVisits"] = max_visits
        return self.query_raw(query)

    def query_raw(self, query: Dict[str,Any]):
        self.katago.stdin.write((json.dumps(query) + "\n").encode())
        input("按任意键继续...")

        self.katago.stdin.flush()

        # print(json.dumps(query))

        line = ""
        while line == "":
            if self.katago.poll():
                time.sleep(1)
                raise Exception("Unexpected katago exit")
            line = self.katago.stdout.readline()
            line = line.decode().strip()
            # print("Got: " + line)
        response = json.loads(line)

        print("sum policy is: ", sum(response["policy"]))
        print("len policy is: ", len(response["policy"]))
        print("min policy is: ", min(response["policy"]))
        print("corresponding to index: ", response["policy"].index(min(response["policy"])))
        print("max policy is: ", max(response["policy"]))
        max_ind = response["policy"].index(max(response["policy"]))
        print("corresponding to index: ", max_ind)
        print("which is: ", str(max_ind//19) + ", " + str(max_ind%19))
        return response

if __name__ == "__main__":
    description = """
    Example script showing how to run KataGo analysis engine and query it from python.
    """
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument(
        "-katago-path",
        help="Path to katago executable",
        required=True,
    )
    parser.add_argument(
        "-config-path",
        help="Path to KataGo analysis config (e.g. cpp/configs/analysis_example.cfg in KataGo repo)",
        required=True,
    )
    parser.add_argument(
        "-model-path",
        help="Path to neural network .bin.gz file",
        required=True,
    )
    args = vars(parser.parse_args())
    print(args)

    katago = KataGo(args["katago_path"], args["config_path"], args["model_path"])

    board = sgfmill.boards.Board(19)
    komi = 6.5
    moves = [
('b', (16, 16)),
('w', (3, 15)),
('b', (16, 2)),
('w', (3, 3)),
('b', (2, 3)),
('w', (2, 4)),
('b', (3, 2)),
('w', (1, 3)),
('b', (2, 2)),
('w', (4, 3)),
('b', (4, 2)),
('w', (5, 15)),
('b', (5, 3)),
('w', (5, 4)),
('b', (3, 4)),
('w', (4, 4)),
('b', (3, 5)),
('w', (1, 4)),
('b', (6, 4)),
('w', (6, 3)),
('b', (5, 2)),
('w', (6, 5)),
('b', (7, 4)),
('w', (5, 6)),
('b', (4, 6)),
('w', (5, 5)),
('b', (4, 7)),
('w', (7, 6)),
('b', (1, 6)),
('w', (5, 7)),
('b', (4, 8)),
('w', (5, 8)),
('b', (4, 9)),
('w', (5, 10)),
('b', (5, 9)),
('w', (6, 9)),
('b', (6, 10)),
('w', (14, 16)),
('b', (7, 9)),
('w', (6, 8)),
('b', (7, 10)),
('w', (5, 11)),
('b', (3, 11)),
('w', (2, 13)),
('b', (16, 14)),
('w', (14, 14)),
('b', (2, 12)),
('w', (14, 2)),
('b', (16, 4)),
('w', (7, 3)),
('b', (8, 4)),
('w', (8, 3)),
('b', (9, 4)),
('w', (9, 3)),
('b', (10, 3)),
('w', (10, 2)),
('b', (11, 2)),
('w', (11, 3)),
('b', (10, 4)),
('w', (9, 2)),
('b', (12, 3)),
('w', (12, 2)),
('b', (11, 4)),
('w', (11, 1)),
# ('b', (8, 7)),
    ]

    displayboard = board.copy()
    for color, move in moves:
        if move != "pass":
            row,col = move
            displayboard.play(row,col,color)
    print(sgfmill.ascii_boards.render_board(displayboard))

    print("Query result: ")
    print(katago.query(board, moves, komi))

    katago.close()