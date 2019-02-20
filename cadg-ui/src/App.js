import React, { Component } from 'react';
import Header from './components/header/header-content';
import Main from './components/main/sidebar';

class App extends Component {
  render() {
    return (
      <div className="App">
          <Header/>
          <Main/>
      </div>
    );
  }
}

export default App;
