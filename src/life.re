type action =
  | StartTimer
  | StopTimer
  | Tick;

type state = {
  running: bool,
  timerId: ref(option(Js.Global.intervalId)),
  board: list(int)
};

let cell = (value: int) => {
  if (value == 1) {
    <span className="cell alive" />
  } else {
    <span className="cell dead" />
  };
};

let life = ReasonReact.reducerComponent("Life");

let make = (_children) => {
  ...life,
  didMount: (self) => {
    self.state.timerId := Some(Js.Global.setInterval(() => {
      self.send(Tick)
    }, 1000));
    ReasonReact.NoUpdate
  },
  willUnmount: (self) => {
    if (self.state.running) {
        switch (self.state.timerId^) {
        | Some(id) => Js.Global.clearInterval(id);
        | None => ()
        }
    }
  },
  willUpdate: ({oldSelf, newSelf}) => {
    if (oldSelf.state.running && !newSelf.state.running) {
      switch (newSelf.state.timerId^) {
      | Some(id) => Js.Global.clearInterval(id);
      | None => ()
      }
    };
    if (!oldSelf.state.running && newSelf.state.running) {
      newSelf.state.timerId := Some(Js.Global.setInterval(() => {
        newSelf.send(Tick) }, 1000));
    };
  },
  initialState: () => {
      running: true,
      timerId: ref(None),
      board: [1,0,0,0,1]
  },
  reducer: (action, state) =>
    switch (action) {
    | StartTimer => ReasonReact.Update({...state, running: true })
    | StopTimer => ReasonReact.Update({...state, running: false })
    | Tick => {
      let newBoard = List.map((item) => {
        if (item == 0) {
          1
        } else {
          0
        };
      }, state.board);
      ReasonReact.Update({...state, board: newBoard})
      }
    },
  render: ({state, send}) => {
    <div>
      <hr />
      (ReasonReact.arrayToElement(Array.of_list(
                  List.map((item) =>
                           cell(item),
                           state.board)
      )))
      <button onClick={_event => send(StartTimer)}>{
        ReasonReact.stringToElement("Start") }</button>
      <button onClick={_event => send(StopTimer)}>{
        ReasonReact.stringToElement("Stop") }</button>
    </div>
  }
};
