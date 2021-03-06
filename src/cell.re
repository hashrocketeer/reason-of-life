let component = ReasonReact.statelessComponent("Cell");

let make = (~cellData: CellData.data, ~onClick, _children) => {
  ...component,
  render: (_self) =>
    if (cellData.value == 1) {
      <span className="cell alive"
        onClick={onClick}
        style=(ReactDOMRe.Style.make(~backgroundColor=cellData.color, ())) />
    } else {
      <span className="cell dead"
        onClick={onClick}
        style=(ReactDOMRe.Style.make(~backgroundColor=cellData.color, ())) />
    }
};
