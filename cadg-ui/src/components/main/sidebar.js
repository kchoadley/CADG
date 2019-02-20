import React, { Component } from 'react';
import { Sidebar, Segment, Menu } from 'semantic-ui-react';
import Main from './main-content'

export default class SidebarContent extends Component {
    state = {
        visible: true
    }

  handleHideClick = () => this.setState({ visible: false })
  handleShowClick = () => this.setState({ visible: true })

  render() {
    return (
      <div>
        <Sidebar.Pushable as={Segment}>
        <Sidebar
            as={Menu}
            animation='push'
            direction='left'
            inverted
            // onHide={this.handleSidebarHide}
            // onVisible={this.handleShowClick}
            vertical
            visible={this.state.visible}
            width='thin'>
            <Menu.Item as='a'>Alerts</Menu.Item>
            <Menu.Item as='a'>Originators</Menu.Item>
            <Menu.Item as='a'>Disseminators</Menu.Item>
        </Sidebar>

        <Sidebar.Pusher>
            <Segment basic>
              <Main/>
            </Segment>
          </Sidebar.Pusher>
        </Sidebar.Pushable>
      </div>
    )
  }
}