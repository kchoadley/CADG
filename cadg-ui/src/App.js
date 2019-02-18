import React, { Component } from 'react';
import './css/App.css';
import HeaderContent from './components/header-content/header-content';
import Sidebar from './components/sidebar/sidebar';
import MainContent from './components/main-content/main-content'

class App extends Component {
  render() {
    return (
      <div className="App">
          <HeaderContent/>
          <Sidebar/>
          <MainContent/>
      </div>
    );
  }
}

export default App;
